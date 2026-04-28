#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// =================================================================
// --- I2C MAGISTRAL CONFIGURATION ---
// =================================================================

// I2C no 0 (INA219 + left TSL2591)
#define I2C0_SDA 21
#define I2C0_SCL 22

// I2C no 1 (right TSL2591)
#define I2C1_SDA 17 
#define I2C1_SCL 16

// I2C addresses
#define ADDR_INA219 0x40
#define ADDR_TSL2591 0x29

// =================================================================
// --- OTHER SENSORS ---
// =================================================================
#define PIN_LIMIT_LEFT 25     // left limit switch
#define PIN_LIMIT_RIGHT 26     // right limit switch
#define PIN_DHT_DATA   32     // DHT22 (one-wire)

// =================================================================
// --- STEPPER MOTOR CONFIG (TB6600) ---
// =================================================================
#define PIN_MOTOR_STEP 12  // steps
#define PIN_MOTOR_DIR  14  // direction
#define PIN_MOTOR_ENA  27  // enable

// Driver and motor parameters
#define STEPS_PER_REV 200     // resolution of stepper motor
#define MICROSTEPPING 8       // microstep parameter (define on stepper motor driver microswitches)
#define MOTOR_MAX_SPEED 1000  // max speed (steps per sec)
#define MOTOR_ACCEL 500       // acceleration

// =================================================================
// --- SYSTEM AND NETWORK PARAMETERS ---
// =================================================================
#define METRICS_INTERVAL 10.0f // metrics sending frequenc
#define TELEMETRY_INTERVAL 5000 // datat sending frequency
#define WIFI_SSID "GooglePixel"
#define WIFI_PASS "12345678"

// NTP servers config
#define NTP_SERVER_1 "pool.ntp.org"
#define NTP_SERVER_2 "time.nist.gov"
#define TIME_ZONE "CET-1CEST,M3.5.0,M10.5.0/3"

#endif // CONFIG_H