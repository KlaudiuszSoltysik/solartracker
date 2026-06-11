#include <Arduino.h>
#include "wifi_manager.h"
#include "config.h"
#include "time_manager.h"
#include "sensor_manager.h"
#include "metrics.h"
#include "motor_controller.h"
#include "mqtt_manager.h"
#include "yaw_controller.h"

unsigned long lastTelemetrySentAt = 0;

void setup()
{
  Serial.begin(115200);
  delay(1000);
  setupWifi();
  initClock();
  initSensors();
  initMetrics(METRICS_INTERVAL);
  initMotor();
  // YawRange yawRange = calibrateYawRange();
  // setYawAngleLimits(yawRange.minAngle, yawRange.maxAngle);
  moveMotorToHomePosition();
  moveMotorByAngle(PARK_POSITION_ANGLE - getCurrentPanelAngle());
  initMqtt();
  //calibrateGearRatio(800);
  //calibrateFullHysteresis360(800);
}

void loop()
{

  handleMotor();
  handleYawController();
  handleMqtt();

  // Temporary simulation of metrics and sensors data collection. Replace with real data collection in the future.
  // if (isTimeToCollectMetrics())
  // {

  //   Metrics actualMetrics = collectMetrics();

  //   Serial.printf("Device ID:     %s\n", actualMetrics.device_id.c_str());
  //   Serial.printf("Free RAM:      %u bytes\n", actualMetrics.freeRam);
  //   Serial.printf("Total RAM:     %u bytes\n", actualMetrics.totalRam);
  //   Serial.printf("Work time:     %u s\n", actualMetrics.uptime);
  //   Serial.printf("Last task time:%u ms\n", actualMetrics.lastTaskDuration);
  //   Serial.printf("Timestamp:     %lu\n", actualMetrics.timestamp);
  //   Serial.printf("Status:        %s\n", actualMetrics.status.c_str());
  //   Serial.println("============================");
  // }

  if (!isMotorMoving() && isTimeToReadSensors())
  {
    SensorData data = readAllSensors();
    Serial.printf("Voltage:       %.2f V\n", data.voltage);
    Serial.printf("Current:       %.2f mA\n", data.current);
    Serial.printf("Power:         %.2f mW\n", data.power);
    Serial.printf("Temperature:   %.2f C\n", data.temperature);
    Serial.printf("Lux (Left):    %lu lux\n", data.luxLeft);
    Serial.printf("Lux (Right):   %lu lux\n", data.luxRight);
    Serial.println("============================");
  }

  if (!isMotorMoving() && millis() - lastTelemetrySentAt >= TELEMETRY_INTERVAL)
  {
    lastTelemetrySentAt = millis();
    SensorData data = readAllSensors();
    publishTelemetry(data);
  }
}
