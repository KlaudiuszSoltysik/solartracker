#pragma once

#include "sensor_manager.h"

void initMqtt();
void handleMqtt();
bool publishTelemetry(const SensorData &data);
bool isMqttConnected();
