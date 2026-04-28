#pragma once

struct Metrics {
    String device_id;
    uint32_t freeRam;
    uint32_t totalRam;
    uint32_t uptime;
    uint32_t lastTaskDuration;
    time_t timestamp;
};

// Initialize collecting of metrics
void initMetrics(float metrics_interval);

// Checking, is it time to start collecting metrics
bool isTimeToCollectMetrics();

// Collecting metrics
Metrics collectMetrics();