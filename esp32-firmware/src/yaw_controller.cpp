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
float minYawAngle = DEFAULT_MIN_YAW_ANGLE;
float maxYawAngle = DEFAULT_MAX_YAW_ANGLE;

void moveToAbsoluteAngle(float targetAngle)
{
    if (!isPanelHomed() || hasMotorFault())
    {
        Serial.println("[YAW] Movement rejected: panel is not homed or motor fault is active.");
        return;
    }

    if (targetAngle < minYawAngle || targetAngle > maxYawAngle)
    {
        Serial.printf("[YAW-LIMIT] Target %.2f deg outside logical range %.2f..%.2f deg. Constraining.\n",
                      targetAngle, minYawAngle, maxYawAngle);
    }

    targetAngle = constrain(targetAngle, minYawAngle, maxYawAngle);

    float currentPanelAngle = getCurrentPanelAngle();
    float angleDiff = targetAngle - currentPanelAngle;

    if (abs(angleDiff) >= MIN_MOVEMENT_ANGLE)
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
        moveToAbsoluteAngle(getCurrentPanelAngle() + correction);
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

    if (elevation <= 0.0)
    {
        Serial.printf("[ASTRO] Sun below horizon. Elevation: %.2f deg. Moving to east limit.\n", elevation);
        return minYawAngle;
    }

    // Use compass azimuth directly: 180 deg means the panel points straight ahead.
    float motorTargetAngle = (float)azimuth;

    Serial.printf("[ASTRO] Time: %lu | Azimuth: %.2f deg | Elevation: %.2f deg | Motor target: %.2f deg\n",
                  now_utc, azimuth, elevation, motorTargetAngle);

    return motorTargetAngle;
}

void handleYawController()
{
    if (millis() - lastYawCheck < YAW_CONTROL_INTERVAL)
        return;
    lastYawCheck = millis();

    if (isMotorMoving())
        return;

    if (!isPanelHomed() || hasMotorFault())
        return;

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
void setYawAngleLimits(float minAngle, float maxAngle)
{
    minYawAngle = minAngle;
    maxYawAngle = maxAngle;
    setMotorAngleLimits(minAngle, maxAngle);
    Serial.printf("[YAW] Angle limits set: %.2f deg to %.2f deg\n", minYawAngle, maxYawAngle);
}
float getCurrentYawAngle() { return getCurrentPanelAngle(); }
