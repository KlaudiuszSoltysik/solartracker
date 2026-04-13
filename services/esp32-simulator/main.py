import time
import os
import json
import random
import logging
import paho.mqtt.client as mqtt

logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s [%(levelname)s] [%(name)s] %(message)s',
    datefmt='%Y-%m-%d %H:%M:%S',
    handlers=[logging.StreamHandler(sys.stdout)]
)

DEVICE_ID = os.environ.get("DEVICE_ID", "test")
BROKER = os.environ.get("MQTT_BROKER", "localhost")
PORT = int(os.environ.get("MQTT_PORT", "1883"))
FREQ = int(os.environ.get("SEND_INTERVAL", "30"))

logger = logging.getLogger(f"{DEVICE_ID}")

telemetry_topic = f"telemetry/device/{DEVICE_ID}"
command_topic = f"controls/device/{DEVICE_ID}"

current_yaw_angle = 90.0 

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        logger.info(f"Connected to MQTT broker at {BROKER}:{PORT}")
        client.subscribe(command_topic)
        logger.info(f"Listening for commands on: {command_topic}")
    else:
        logger.error(f"Connection error, code: {rc}", exc_info=True)

def on_message(client, userdata, msg):
    global current_yaw_angle
    try:
        payload = json.loads(msg.payload.decode())
        logger.info(f"Received command | Topic: {msg.topic} | Data: {payload}")
        
        if "target_yaw" in payload:
            current_yaw_angle = float(payload["target_yaw"])
            logger.info(f"Rotating to: {current_yaw_angle}°")
    except Exception as e:
        logger.error(f"Error parsing message: {e}", exc_info=True)

def generate_mock_telemetry():
    return {
        "timestamp": int(time.time()),
        "voltage_v": round(random.uniform(28.5, 34.2), 2),
        "current_i": round(random.uniform(0.5, 10.0), 2),
        "irradiance_wm2": random.randint(200, 950),
        "temp_c": round(random.uniform(15.0, 45.0), 1),
        "yaw_angle_deg": current_yaw_angle,
        "status": "OK"
    }

def main():
    client = mqtt.Client(client_id=DEVICE_ID)
    
    client.on_connect = on_connect
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
        telemetry_data = generate_mock_telemetry()
        payload_json = json.dumps(telemetry_data)
        
        info = client.publish(telemetry_topic, payload_json, qos=1)
        
        logger.info(f"Sent telemetry: {payload_json}")
        
        time.sleep(FREQ)

if __name__ == "__main__":
    main()
