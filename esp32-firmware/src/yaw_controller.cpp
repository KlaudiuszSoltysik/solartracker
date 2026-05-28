#include <Arduino.h>
#include <SolarCalculator.h>
#include "yaw_controller.h"
#include "sensor_manager.h"
#include "motor_controller.h"
#include "time_manager.h"
#include "config.h"

unsigned long lastYawCheck = 0;
TrackingMode currentMode = MODE_HYBRID;
float targetManualAngle = 0.0f;

void moveToAbsoluteAngle(float targetAngle)
{
    float currentPanelAngle = getCurrentPanelAngle();
    float angleDiff = targetAngle - currentPanelAngle;

    if (abs(angleDiff) > MIN_MOVEMENT_ANGLE)
    {
        moveMotorByAngle(angleDiff);
    }
}

void executeSensorLogic(SensorData data)
{
    int diff = (int)data.luxLeft - (int)data.luxRight;
    if (abs(diff) > DEADBAND_LUX)
    {
        float correction;

        if (diff > 0)
        {
            correction = -STEP_ANGLE; // If condition is met
        }
        else
        {
            correction = STEP_ANGLE; // If condition is NOT met
        }
        moveMotorByAngle(correction);
        Serial.printf("[YAW-SENSOR] Correction: %.1f deg (Lux difference: %d)\n", correction, diff);
    }
    else
    {
        Serial.printf("[YAW-SENSOR] Optimal position.\n");
    }
}

// Calculate target angle based on astronomical calculations
float calculateLocalAstroAngle()
{
    // Get current time in UTC
    time_t now_utc = getUnixTime();

    // If time is not valid, return 0 (or some default angle)
    if (now_utc < 10000)
    {
        return 0.0f;
    }

    // Calculate sun position (azimuth and elevation) based on current time and location
    double azimuth, elevation;

    calcHorizontalCoordinates(now_utc, LATITUDE, LONGITUDE, azimuth, elevation);

    // Convert azimuth to motor angle (assuming 0 deg = South, positive clockwise)
    float motorTargetAngle = (float)azimuth - 180.0f;

    Serial.printf("[ASTRO] Time: %lu | Azimuth: %.2f deg | Elevation: %.2f deg | Motor target: %.2f deg\n",
                  now_utc, azimuth, elevation, motorTargetAngle);

    return motorTargetAngle;
}

void handleYawController()
{
    if (millis() - lastYawCheck < YAW_CONTROL_INTERVAL)
        return;
    lastYawCheck = millis();

    SensorData data = readAllSensors();

    switch (currentMode)
    {
    case MODE_SENSOR:
        executeSensorLogic(data);
        break;

    case MODE_ASTRO:
        moveToAbsoluteAngle(calculateLocalAstroAngle());
        break;

    case MODE_HYBRID:
        if (data.luxLeft < CLOUD_THRESHOLD_LUX && data.luxRight < CLOUD_THRESHOLD_LUX)
        {
            Serial.println("[YAW-HYBRID] Dark/Cloudy! Switching to Astro position.");
            moveToAbsoluteAngle(calculateLocalAstroAngle());
        }
        else
        {
            executeSensorLogic(data);
        }
        break;

    case MODE_MANUAL:
        moveToAbsoluteAngle(targetManualAngle);
        break;
    }
}

// --- Setters and Getters ---
void setTrackingMode(TrackingMode newMode)
{
    currentMode = newMode;
    Serial.printf("[YAW] Switching mode to: %d\n", newMode);
}
void setManualTargetAngle(float angle) { targetManualAngle = angle; }
float getCurrentYawAngle() { return getCurrentPanelAngle(); }
