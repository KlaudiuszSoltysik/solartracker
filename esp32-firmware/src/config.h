#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// =================================================================
// --- I2C MAGISTRAL CONFIGURATION ---
// =================================================================

// I2C no 0 (INA226 + left TSL2591)
#define I2C0_SDA 21
#define I2C0_SCL 22

// I2C no 1 (right TSL2591)
#define I2C1_SDA 17 
#define I2C1_SCL 16

// I2C addresses
#define ADDR_INA226 0x40
#define ADDR_TSL2591 0x29
#define INA226_SHUNT_OHMS 0.1f
#define INA226_MAX_CURRENT_A 0.8f

// =================================================================
// --- OTHER SENSORS ---
// =================================================================
#define PIN_LIMIT_LEFT 25     // left limit switch
#define PIN_LIMIT_RIGHT 26     // right limit switch

// =================================================================
// --- STEPPER MOTOR CONFIG (TB6600) ---
// =================================================================
#define PIN_MOTOR_STEP 12  // steps
#define PIN_MOTOR_DIR  14  // direction
#define PIN_MOTOR_ENA  27  // enable

// Driver and motor parameters
#define STEPS_PER_REV 200     // resolution of stepper motor
#define MICROSTEPPING 4       // microstep parameter (define on stepper motor driver microswitches)
#define MOTOR_MAX_SPEED 1000  // max speed (steps per sec)
#define MOTOR_ACCEL 500       // acceleration
#define GEAR_RATIO 30.0f       // gearbox ratio (number of motor revolutions needed for one full panel rotation)
#define MOTOR_DIRECTION_SIGN -1 // motor direction correction relative to panel angle
#define HOME_DIRECTION_SIGN 1   // motor direction used to reach the physical left home limit
#define DEFAULT_MIN_YAW_ANGLE 105.5f
#define DEFAULT_MAX_YAW_ANGLE 255.5f
#define PARK_POSITION_ANGLE 180.0f
#define HOMING_TIMEOUT_MS 60000UL
#define HOMING_MAX_TRAVEL_ANGLE 180.0f

// =================================================================
// --- YAW CONTROLLER CONFIG ---
// =================================================================
#define YAW_CONTROL_INTERVAL 3000  // How often in ms we check astro/manual yaw targets
#define SENSOR_TRACK_CHECK_INTERVAL 60000 // How often in ms sensors can start a new correction cycle
#define SENSOR_CORRECTION_INTERVAL 3000   // How often in ms sensors correct while tracking is active
#define SENSOR_CORRECTION_START_PERCENT 12.0f // Start sensor tracking above this relative lux difference
#define SENSOR_CORRECTION_STOP_PERCENT 5.0f   // Stop sensor tracking below this relative lux difference
#define SENSOR_STEP_MEDIUM_PERCENT 20.0f      // Use medium correction step above this relative lux difference
#define SENSOR_STEP_LARGE_PERCENT 30.0f       // Use large correction step above this relative lux difference
#define SENSOR_STEP_MAX_PERCENT 50.0f         // Use max correction step above this relative lux difference
#define SENSOR_STEP_MEDIUM_ANGLE 1.0f         // Medium sensor correction step in degrees
#define SENSOR_STEP_LARGE_ANGLE 2.0f          // Large sensor correction step in degrees
#define SENSOR_STEP_MAX_ANGLE 3.0f            // Max sensor correction step in degrees
#define CLOUD_THRESHOLD_LUX 200    // Cloudiness threshold
#define STEP_ANGLE 0.5f            // Correction step (in degrees)
#define MIN_MOVEMENT_ANGLE 0.5f    // Minimum movement angle (in degrees)
#define LIMIT_SWITCH_ANGLE_TOLERANCE 10.0f // Max allowed angle error when a limit switch is active
// Physical left limit angle. Panel points straight ahead at 180 deg.
#define HOME_POSITION_ANGLE 105.0f

// =================================================================
// --- GPS LOCATION (For astronomical calculations) ---
// =================================================================
#define LATITUDE 52.44   // Geographic latitude 
#define LONGITUDE 16.60  // Geographic longitude

// =================================================================
// --- SYSTEM AND NETWORK PARAMETERS ---
// =================================================================
#define METRICS_INTERVAL 10.0f // metrics sending frequency
#define TELEMETRY_INTERVAL 30000 // data sending frequency (milliseconds)
#define SENSORS_READ_INTERVAL 10.0f // sensors reading frequency (seconds)

// NTP servers config
#define NTP_SERVER_1 "pool.ntp.org"
#define NTP_SERVER_2 "time.nist.gov"
#define TIME_ZONE "CET-1CEST,M3.5.0,M10.5.0/3"

// MQTT config
#define DEVICE_ID "ESP_001"
#define MQTT_BROKER_URI "wss://mqtt.260824.xyz/ws"
#define MQTT_RECONNECT_INTERVAL 60000
#define MQTT_TELEMETRY_TOPIC_PREFIX "telemetry/device/"
#define MQTT_COMMAND_TOPIC_PREFIX "controls/device/"
#define LUX_TO_IRRADIANCE_DIVISOR 125.0f

#endif // CONFIG_H
