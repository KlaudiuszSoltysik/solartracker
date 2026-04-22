# ESP32 Simulator

This is a Python script that simulates an ESP32 device connected to a MQTT broker. The ESP32 simulator allows you to test and control the device's behavior using commands sent from the MQTT broker.

## Prerequisites

- Install Python 3.x on your system.
- Install `paho-mqtt` library by running `pip install paho-mqtt`.
- Set up the MQTT broker (e.g., `localhost:1883`) and the ESP32 device's configuration file (`config.json`).

## Configuration File

```json
{
  "DEVICE_ID": "ESP_test",
  "MQTT_BROKER": "localhost",
  "MQTT_PORT": 1883,
  "SEND_INTERVAL": 30
}
```

## Main Script

```python
import json
import logging
import os
import random
import sys
import time

from dotenv import load_dotenv
from paho.mqtt.client import CallbackAPIVersion

load_dotenv()

DEVICE_ID = os.environ.get("DEVICE_ID", "ESP_test")
BROKER = os.environ.get("MQTT_BROKER", "localhost")
PORT = int(os.environ.get("MQTT_PORT", "1883"))
FREQ = int(os.environ.get("SEND_INTERVAL", "30"))

logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s [%(levelname)s] [%(name)s] %(message)s',
    datefmt='%Y-%m-%d %H:%M:%S',
    handlers=[logging.StreamHandler(sys.stdout)]
)

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
        "current_a": round(random.uniform(0.5, 10.0), 2),
        "irradiance_wm2": random.randint(200, 950),
        "temp_c": round(random.uniform(15.0, 45.0), 1),
        "yaw_angle_deg": current_yaw_angle,
        "status": "OK"
    }

def main():
    client = mqtt.Client(CallbackAPIVersion.VERSION2, client_id=DEVICE_ID)
    client.username_pw_set(RABBITMQ_USERNAME, RABBITMQ_PASSWORD)
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
```

## Usage

- Run the script using `python services/esp32-simulator/main.py`.
- The ESP32 simulator will connect to the MQTT broker and start sending commands.
- You can use the `generate_mock_telemetry` function to send mock telemetry data.

## Notes

- This script is a simplified version of an ESP32 device control system. It does not include any actual hardware or software components.
- The MQTT broker configuration file (`config.json`) should be set up with the correct IP address, port, and credentials for your ESP32 device.
- You can modify the `generate_mock_telemetry` function to send more complex telemetry data as needed.

## Contributing

If you want to contribute to this project, please follow these guidelines:

1. Fork the repository on GitHub.
2. Create a new branch: `git checkout -b feature/new-feature`.
3. Make your changes and commit them: `git add <file>.<line>`.
4. Push your changes: `git push origin feature/new-feature`.
5. Open a pull request to the maintainers.

Feel free to open an issue if you have any questions or need help with specific features.