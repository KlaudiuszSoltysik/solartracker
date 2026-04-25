import json
import logging
import os
import random
import sys
import time

import paho.mqtt.client as mqtt
from dotenv import load_dotenv
from paho.mqtt.enums import CallbackAPIVersion

load_dotenv()

DEVICE_ID = os.environ.get("DEVICE_ID", "ESP_test")
BROKER = os.environ.get("MQTT_BROKER", "localhost")
PORT = int(os.environ.get("MQTT_PORT", "1883"))
FREQ = int(os.environ.get("SEND_INTERVAL", "30"))
RABBITMQ_USERNAME = os.environ.get("RABBITMQ_USERNAME", "admin")
RABBITMQ_PASSWORD = os.environ.get("RABBITMQ_PASSWORD", "admin")

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] [%(name)s] %(message)s",
    datefmt="%Y-%m-%d %H:%M:%S",
    handlers=[logging.StreamHandler(sys.stdout)]
)

logger = logging.getLogger(f"{DEVICE_ID}")

telemetry_topic = f"telemetry/device/{DEVICE_ID}"
command_topic = f"controls/device/{DEVICE_ID}"

current_yaw_angle = 90.0


def on_connect(client, userdata, flags, rc):
    if rc == 0:
        logger.info(f"Connected to MQTT broker at {BROKER}:{PORT}.")
        client.subscribe(command_topic)
        logger.info(f"Listening for commands on: {command_topic}.")
    else:
        logger.error(f"Connection error, code: {rc}.", exc_info=True)


def on_disconnect(client, userdata, disconnect_flags, rc):
    logger.warning(f"Disconnected from MQTT broker! Code: {rc}")


def on_message(client, userdata, msg):
    global current_yaw_angle
    try:
        payload = json.loads(msg.payload.decode())
        logger.info(f"Received command | Topic: {msg.topic} | Data: {payload}.")

        if "target_yaw" in payload:
            current_yaw_angle = float(payload["target_yaw"])
            logger.info(f"Rotating to: {current_yaw_angle}°.")
    except Exception as e:
        logger.error(f"Error parsing message: {e}.", exc_info=True)


def generate_mock_telemetry():
    return {
        "timestamp": int(time.time()),
        "voltage_v": round(random.uniform(28.5, 34.2), 2),
        "current_a": round(random.uniform(0.05, 1.0), 2),
        "irradiance_wm2": random.randint(200, 950),
        "temp_c": round(random.uniform(15.0, 45.0), 1),
        "yaw_angle_deg": current_yaw_angle,
        "status": "OK"
    }


def main():
    client = mqtt.Client(CallbackAPIVersion.VERSION2, client_id=DEVICE_ID)
    client.username_pw_set(RABBITMQ_USERNAME, RABBITMQ_PASSWORD)
    client.on_connect = on_connect
    client.on_disconnect = on_disconnect
    client.on_message = on_message

    while True:
        try:
            logger.info(f"Connecting device: {DEVICE_ID} to MQTT broker at {BROKER}:{PORT}...")
            client.connect(BROKER, PORT, keepalive=60)
            break
        except Exception as e:
            logger.error(f"Connection error: {e}. Retrying in 5 seconds...")
            time.sleep(5)

    client.loop_start()

    while True:
        if not client.is_connected():
            logger.warning("Not connected to broker. Waiting...")
            time.sleep(2)
            continue

        telemetry_data = generate_mock_telemetry()
        payload_json = json.dumps(telemetry_data)

        info = client.publish(telemetry_topic, payload_json, qos=1)

        try:
            info.wait_for_publish(timeout=15)

            if info.is_published():
                logger.info(f"Sent telemetry: {payload_json}.")
            else:
                logger.error("Failed to send telemetry: Timeout reached.")
        except RuntimeError as e:
            logger.error(f"Failed to send telemetry: {e}")

        time.sleep(FREQ)


if __name__ == "__main__":
    main()
