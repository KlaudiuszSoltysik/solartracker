#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Adafruit_INA219.h>
#include <Adafruit_TSL2591.h>
#include <DHT.h>
#include <Wire.h>
    
struct SensorData {
    float voltage;     // V
    float current;     // mA
    float power;       // mW
    float temperature; // C
    float humidity;    // %
    uint16_t luxLeft;  // lx
    uint16_t luxRight; // lx
};

// sensor initialization
void initSensors();
// read and calculate data drom sensors
SensorData readAllSensors();

#endif