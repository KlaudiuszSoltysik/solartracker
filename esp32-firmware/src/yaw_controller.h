#pragma once

// Definition of tracker operating modes
enum TrackingMode {
    MODE_SENSOR,      // 1. Follow only light sensors
    MODE_ASTRO,       // 2. Follow calculated sun position (from server)
    MODE_HYBRID,      // 3. Sensors + fallback to sun position during cloudiness
    MODE_MANUAL       // 4. Manual control from the app
};

// Main logic function (must be called in loop)
void handleYawController();

// --- API interface functions ---

// Change the current operating mode
void setTrackingMode(TrackingMode newMode);

// Set the target angle from the app slider
void setManualTargetAngle(float angle);

// Set calibrated yaw movement range
void setYawAngleLimits(float minAngle, float maxAngle);

// Get the current physical angle of the panel
float getCurrentYawAngle();
