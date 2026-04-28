#include <Arduino.h>
#include "wifi_manager.h"
#include "config.h"
#include "time_manager.h"
#include "sensor_manager.h"
#include "metrics.h"
#include "motor_controller.h"

void setup()
{
  Serial.begin(115200);
  delay(1000);
  setupWifi();
  initClock();
  initSensors();
  initMetrics(METRICS_INTERVAL);
  initMotor();
}

void loop()
{
  // Temporary simulation of metrics and sensors data collection. Replace with real data collection in the future.
  if (isTimeToCollectMetrics())
  {

    Metrics actualMetrics = collectMetrics();

    Serial.printf("Device ID:     %s\n", actualMetrics.device_id.c_str());
    Serial.printf("Free RAM:      %u bytes\n", actualMetrics.freeRam);
    Serial.printf("Total RAM:     %u bytes\n", actualMetrics.totalRam);
    Serial.printf("Work time:     %u s\n", actualMetrics.uptime);
    Serial.printf("Last task time:%u ms\n", actualMetrics.lastTaskDuration);
    Serial.printf("Timestamp:     %lu\n", actualMetrics.timestamp);
    Serial.println("============================");
  }

  if (isTimeToReadSensors())
  {
    SensorData data = readAllSensors(true);
    Serial.printf("Voltage:       %.2f V\n", data.voltage);
    Serial.printf("Current:       %.2f mA\n", data.current);
    Serial.printf("Power:         %.2f mW\n", data.power);
    Serial.printf("Temperature:   %.2f C\n", data.temperature);
    Serial.printf("Humidity:      %.2f %%\n", data.humidity);
    Serial.printf("Lux (Left):    %lu lux\n", data.luxLeft);
    Serial.printf("Lux (Right):   %lu lux\n", data.luxRight);
    Serial.println("============================");
  }
}
