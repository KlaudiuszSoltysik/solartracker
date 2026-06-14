# ESP32 Solar Tracker Firmware

Firmware for an ESP32-based single-axis solar tracker. The controller reads light, voltage/current, and temperature sensors, drives a stepper motor through a A4988 driver, uses limit switches for homing/safety, and exchanges telemetry/commands with the backend over MQTT via WSS.

## Main Features

- Yaw tracking with four modes:
  - `MODE_HYBRID`: light sensors with astronomical fallback in low light
  - `MODE_SENSOR`: light sensors only
  - `MODE_ASTRO`: sun azimuth calculation only
  - `MODE_MANUAL`: target angle from MQTT command
- Stepper motor control using `AccelStepper`
- Left/right limit switch safety checks
- Homing with timeout and maximum travel guard
- Eco Mode: motor coils are disabled after movement
- INA226 power/current/voltage measurement
- Two TSL2591 light sensors
- BMP280 temperature measurement
- MQTT telemetry and remote yaw commands over `wss://`
- Optional RAM buffering for telemetry when MQTT is offline
- NTP time synchronization for astronomical tracking

## Hardware

Current pin configuration is defined in `src/config.h`.

### I2C Bus 0

| Device | Purpose | Pins |
|---|---|---|
| INA226 | voltage/current/power | SDA `21`, SCL `22` |
| Left TSL2591 | left light sensor | SDA `21`, SCL `22` |
| BMP280 | temperature sensor | SDA `21`, SCL `22` |

### I2C Bus 1

| Device | Purpose | Pins |
|---|---|---|
| Right TSL2591 | right light sensor | SDA `17`, SCL `16` |

### Motor And Limit Switches

| Signal | Pin |
|---|---:|
| A4988 STEP | `12` |
| A4988 DIR | `14` |
| A4988 ENA | `27` |
| Left limit switch | `25` |
| Right limit switch | `26` |

Limit switches are configured as `INPUT_PULLUP`, so an active switch is expected to pull the input to `LOW`.

## Configuration

Most runtime constants are in `src/config.h`.

Important current values:

```cpp
#define DEVICE_ID "ESP_001"
#define MQTT_BROKER_URI "wss://mqtt.260824.xyz/ws"

#define DEFAULT_MIN_YAW_ANGLE 105.5f
#define DEFAULT_MAX_YAW_ANGLE 255.5f
#define PARK_POSITION_ANGLE 180.0f

#define HOMING_TIMEOUT_MS 60000UL
#define HOMING_MAX_TRAVEL_ANGLE 180.0f
```

Motor assumptions:

```cpp
#define STEPS_PER_REV 200
#define MICROSTEPPING 4
#define GEAR_RATIO 30.0f
#define MOTOR_DIRECTION_SIGN -1
#define HOME_DIRECTION_SIGN 1
```

The current physical setup assumes the panel points straight ahead at about `180 deg`, with motion limits around `105.5 deg` to `255.5 deg`.

## Secrets

Create `src/secrets.h` locally. Do not commit it.

Example:

```cpp
#pragma once

#define WIFI_SSID "your_wifi"
#define WIFI_PASS "your_password"
#define MQTT_USERNAME "mqtt_username"
#define MQTT_PASSWORD "mqtt_password"
#define MQTT_DEVICE_KEY "backend_device_key"
```

Make sure `src/secrets.h` is ignored by git before pushing.

## MQTT

The firmware uses the native ESP-IDF MQTT client because the broker is exposed as MQTT over secure WebSocket.

Broker:

```text
wss://mqtt.260824.xyz/ws
```

Telemetry topic:

```text
telemetry/device/ESP_001
```

Command topic:

```text
controls/device/ESP_001
```

### Telemetry Payload

Example telemetry sent by ESP32:

```json
{
  "key": "backend_device_key",
  "timestamp": 1760000000,
  "voltage_v": 12.9,
  "current_a": 0.08,
  "irradiance_wm2": 250.4,
  "temp_c": 22.5,
  "yaw_angle_deg": 180.0,
  "status": "OK"
}
```

`key` is required by the backend telemetry processor.

### Offline Telemetry Buffer

Telemetry buffering can be enabled or disabled in `src/config.h`:

```cpp
#define MQTT_BUFFER_TELEMETRY true
#define MQTT_TELEMETRY_BUFFER_SIZE 60
#define MQTT_QUEUE_FLUSH_INTERVAL 1000
```

When `MQTT_BUFFER_TELEMETRY` is `true`:

- current telemetry is sent immediately if MQTT is connected
- if MQTT is disconnected, the ready JSON payload is stored in a RAM ring buffer
- the buffer stores up to 60 telemetry messages
- if the buffer is full, the oldest message is overwritten
- after MQTT reconnects, queued messages are sent one by one
- queued messages are flushed at most once per `MQTT_QUEUE_FLUSH_INTERVAL`
- queued messages are not flushed while the motor is moving

With the current telemetry interval of 30 seconds, a 60-message buffer stores about 30 minutes of offline telemetry.

If backend compatibility becomes a problem, set:

```cpp
#define MQTT_BUFFER_TELEMETRY false
```

In that mode, telemetry behaves like the original implementation: if MQTT is disconnected, the sample is skipped instead of buffered.

### Command Payload

Manual yaw command:

```json
{
  "target_yaw": 180
}
```

Receiving `target_yaw` switches the firmware to `MODE_MANUAL` and moves toward the requested angle, constrained to the configured yaw limits.

## Sensor Yaw Logic

Sensor-based yaw tracking compares the two TSL2591 lux readings.

The relative difference is calculated as:

```text
diffPercent = abs(luxLeft - luxRight) / ((luxLeft + luxRight) / 2) * 100
```

Current thresholds:

| Relative difference | Action |
|---:|---|
| `<= 3%` | stop correction, optimal |
| `3%..8%` | dead zone |
| `>= 8%` | start/continue correction |
| `>= 8%` | step `1.5 deg` |
| `>= 20%` | step `3.0 deg` |
| `>= 35%` | step `5.0 deg` |

Sensor checks:

```cpp
#define SENSOR_TRACK_CHECK_INTERVAL 60000
#define SENSOR_CORRECTION_INTERVAL 3000
```

This means a new correction cycle can start roughly once per minute, but once correction is active it updates every 3 seconds until the panel reaches the stop threshold.

## Astro Logic

Astronomical tracking uses `SolarCalculator` with:

```cpp
#define LATITUDE 52.44
#define LONGITUDE 16.60
```

If the sun elevation is below the horizon, the panel moves to the east/left limit angle.

## Motor Safety

The motor controller tracks:

- `panelHomed`
- `motorFault`
- current angle from stepper position
- logical yaw limits
- physical limit switch states

Movement is rejected if:

- panel is not homed
- motor fault is active
- requested angle is outside logical limits, after constraining

Faults are raised when:

- both limit switches are active at once
- a limit switch activates far from its expected logical angle
- homing/calibration exceeds timeout
- homing/calibration exceeds maximum travel

## Build And Upload

This is a PlatformIO project.

Build:

```powershell
platformio run
```

Upload:

```powershell
platformio run --target upload
```

Serial monitor:

```powershell
platformio device monitor
```

Monitor speed is configured as:

```ini
monitor_speed = 115200
```

## Typical Startup Flow

Current `setup()` flow:

1. Start Serial
2. Connect Wi-Fi
3. Synchronize time over NTP
4. Initialize sensors
5. Initialize metrics timer
6. Initialize motor
7. Home the panel
8. Initialize MQTT client

Expected MQTT logs after a successful connection:

```text
[MQTT] Client initialized for wss://mqtt.260824.xyz/ws as ESP_001
[MQTT] Connecting to wss://mqtt.260824.xyz/ws as ESP_001
[MQTT] Connected via WSS.
[MQTT] Subscribing to controls/device/ESP_001
```

## Notes

- The tracker uses a self-locking worm gearbox, so disabling motor coils after movement is expected.
- MQTT reconnect is handled manually to avoid blocking motor stepping during network outages.
- If MQTT fails while the motor is moving, reconnect is delayed until the motor stops.
- If telemetry buffering is enabled, offline samples are kept only in RAM and are lost after ESP32 reset.
- The CA certificate chain for `mqtt.260824.xyz` is embedded in `src/mqtt_manager.cpp`. If the broker certificate chain changes, MQTT TLS may need an updated CA certificate.
