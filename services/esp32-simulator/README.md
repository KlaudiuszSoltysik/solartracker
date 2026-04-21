# ESP32 Simulator Module

This module is designed to simulate an ESP32 device connected to a MQTT broker. The main function `main()` connects to the MQTT broker, subscribes to the telemetry topic, and publishes mock telemetry data every 5 seconds.

## Technical Architecture

- **Setup**: The module requires the following environment variables:
  - `DEVICE_ID`: The unique identifier for the ESP32 device.
  - `MQTT_BROKER`: The IP address or hostname of the MQTT broker.
  - `MQTT_PORT`: The port number used by the MQTT broker.
  - `SEND_INTERVAL`: The interval at which telemetry data is published in seconds.

- **Functions**:
  - `on_connect(client, userdata, flags, rc)`: Handles connection to the MQTT broker and subscribes to the telemetry topic.
  - `on_message(client, userdata, msg)`: Processes incoming messages from the MQTT broker. If a command is received, it updates the current yaw angle.

## Usage

1. **Install Dependencies**: Ensure you have installed the necessary dependencies for this module:
   ```bash
   pip install paho-mqtt
   ```

2. **Run the Module**: Execute the script to start the simulation.
   ```bash
   python main.py
   ```

3. **Telemetry Simulation**:
   - The `generate_mock_telemetry()` function generates mock telemetry data every 5 seconds.
   - The `main()` function connects to the MQTT broker, subscribes to the telemetry topic, and publishes the mock telemetry data.

## Example Usage

- Connect to the MQTT broker: `python main.py`
- Subscribe to the telemetry topic: `python main.py`
- Publish mock telemetry data: `python main.py`

## Notes
- The module is designed for internal use only. External developers should refer to the official ESP32 SDK documentation.