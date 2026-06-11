#include <Arduino.h>
#include <SolarCalculator.h>
#include "yaw_controller.h"
#include "sensor_manager.h"
#include "motor_controller.h"
#include "time_manager.h"
#include "config.h"

unsigned long lastYawCheck = 0;
unsigned long lastSensorCheck = 0;
TrackingMode currentMode = MODE_HYBRID;
float targetManualAngle = 0.0f;
float minYawAngle = DEFAULT_MIN_YAW_ANGLE;
float maxYawAngle = DEFAULT_MAX_YAW_ANGLE;
bool sensorCorrectionActive = false;

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

bool isTimeForSensorLogic()
{
    unsigned long interval = sensorCorrectionActive
                                 ? SENSOR_CORRECTION_INTERVAL
                                 : SENSOR_TRACK_CHECK_INTERVAL;

    unsigned long now = millis();
    if (lastSensorCheck != 0 && now - lastSensorCheck < interval)
        return false;

    lastSensorCheck = now;
    return true;
}

float getLuxDifferencePercent(int absDiff, SensorData data)
{
    float averageLux = ((float)data.luxLeft + (float)data.luxRight) / 2.0f;
    if (averageLux <= 0.0f)
        return 0.0f;

    return ((float)absDiff / averageLux) * 100.0f;
}

float getSensorCorrectionStep(float diffPercent)
{
    if (diffPercent >= SENSOR_STEP_MAX_PERCENT)
        return SENSOR_STEP_MAX_ANGLE;

    if (diffPercent >= SENSOR_STEP_LARGE_PERCENT)
        return SENSOR_STEP_LARGE_ANGLE;

    if (diffPercent >= SENSOR_STEP_MEDIUM_PERCENT)
        return SENSOR_STEP_MEDIUM_ANGLE;

    return STEP_ANGLE;
}

void executeSensorLogic(SensorData data)
{
    int diff = (int)data.luxLeft - (int)data.luxRight;
    int absDiff = abs(diff);
    float diffPercent = getLuxDifferencePercent(absDiff, data);

    if (!sensorCorrectionActive && diffPercent <= SENSOR_CORRECTION_START_PERCENT)
    {
        Serial.printf("[YAW-SENSOR] Waiting. Lux difference: %d (%.1f%%), start threshold: %.1f%%\n",
                      diff, diffPercent, SENSOR_CORRECTION_START_PERCENT);
        return;
    }

    if (diffPercent <= SENSOR_CORRECTION_STOP_PERCENT)
    {
        sensorCorrectionActive = false;
        Serial.printf("[YAW-SENSOR] Optimal position. Lux difference: %d (%.1f%%)\n", diff, diffPercent);
        return;
    }

    sensorCorrectionActive = true;

    if (diffPercent > SENSOR_CORRECTION_STOP_PERCENT)
    {
        float correction;
        float correctionStep = getSensorCorrectionStep(diffPercent);

        if (diff > 0)
        {
            correction = -correctionStep; // Left sensor sees more light, rotate toward it
        }
        else
        {
            correction = correctionStep; // Right sensor sees more light, rotate toward it
        }
        moveToAbsoluteAngle(getCurrentPanelAngle() + correction);
        Serial.printf("[YAW-SENSOR] Correction: %.1f deg (Lux difference: %d, %.1f%%)\n",
                      correction, diff, diffPercent);
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

    switch (currentMode)
    {
    case MODE_SENSOR:
        if (!isTimeForSensorLogic())
            return;

        executeSensorLogic(readAllSensors());
        break;

    case MODE_ASTRO:
        moveToAbsoluteAngle(calculateLocalAstroAngle());
        break;

    case MODE_HYBRID:
    {
        if (!isTimeForSensorLogic())
            return;

        SensorData data = readAllSensors();
        if (data.luxLeft < CLOUD_THRESHOLD_LUX && data.luxRight < CLOUD_THRESHOLD_LUX)
        {
            sensorCorrectionActive = false;
            Serial.println("[YAW-HYBRID] Dark/Cloudy! Switching to Astro position.");
            moveToAbsoluteAngle(calculateLocalAstroAngle());
        }
        else
        {
            executeSensorLogic(data);
        }
        break;
    }

    case MODE_MANUAL:
        moveToAbsoluteAngle(targetManualAngle);
        break;
    }
}

// --- Setters and Getters ---
void setTrackingMode(TrackingMode newMode)
{
    currentMode = newMode;
    sensorCorrectionActive = false;
    lastSensorCheck = 0;
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
