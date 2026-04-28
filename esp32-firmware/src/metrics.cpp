#include <Arduino.h>
#include <Ticker.h>
#include "metrics.h"
#include <time_manager.h>

Ticker metricsTimer;
volatile bool _metricsFlag = false;
uint32_t lastTaskDuration = 0; 

void onMetricsTimerTick() {
    _metricsFlag = true;
}

bool isTimeToCollectMetrics() {
    if (_metricsFlag) {
        _metricsFlag = false; 
        return true;
    }
    return false;
}

Metrics collectMetrics() {
    Metrics data;

    data.device_id = "esp-32";
    data.freeRam= ESP.getFreeHeap();
    data.totalRam = ESP.getHeapSize();
    data.uptime = millis() / 1000;
    data.lastTaskDuration = random(2,10);
    data.timestamp = getUnixTime();

    return data;
}

void initMetrics(float metrics_interval) {
    // Cyclic collecting metrics in the background
    metricsTimer.attach(metrics_interval, onMetricsTimerTick);
    Serial.println("Metrics are collecting in the background.");
}