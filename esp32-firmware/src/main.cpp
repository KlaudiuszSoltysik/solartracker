#include <Arduino.h>
#include "wifi_manager.h"
#include "config.h"
#include "time_manager.h"
#include "sensor_manager.h"
#include "metrics.h"


void setup() {
  Serial.begin(115200);
  delay(1000);
  setupWifi();
  initClock();
  initSensors();
  initMetrics(METRICS_INTERVAL);
}

void loop() {
// SensorData currentData = readAllSensors();
  
//   Serial.printf("Panel: %.2fV | %.2fmA | Nasłonecznienie L:%u R:%u\n", 
//                 currentData.voltage, currentData.current, 
//                 currentData.luxLeft, currentData.luxRight);
                
//   delay(2000); 

  if (isTimeToCollectMetrics()) {
        
        Metrics actualMetrics = collectMetrics();
        
        Serial.printf("Device ID:        %s\n", actualMetrics.device_id.c_str());         
        Serial.printf("Free RAM:        %u bytes\n", actualMetrics.freeRam);
        Serial.printf("Total RAM:    %u bytes\n", actualMetrics.totalRam);
        Serial.printf("Work time:  %u s\n", actualMetrics.uptime);
        Serial.printf("Last task time:     %u ms\n", actualMetrics.lastTaskDuration);
        Serial.printf("Timestamp:        %lu\n", actualMetrics.timestamp);        
        Serial.println("======================");
        
    }
}
