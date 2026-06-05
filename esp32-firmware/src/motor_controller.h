#pragma once

// Inititalize PINs, speeds and safety switches
void initMotor();

// Main function to steering motor
void handleMotor();

// Rotare per angle
void moveMotorByAngle(float angle);

// Safety stop
void stopMotor();

// Move to home position (using limit switch)
bool moveMotorToHomePosition();

// Actual position of the panel (for API)
float getCurrentPanelAngle();

// Current position reliability state
bool isPanelHomed();
bool hasMotorFault();
void clearMotorFault();
void setMotorAngleLimits(float minAngle, float maxAngle);

struct YawRange
{
    long minSteps;
    long maxSteps;
    float minAngle;
    float maxAngle;
    float rangeAngle;
};

// Calibrate yaw range by moving from left limit switch to right limit switch
YawRange calibrateYawRange();

// Calibration of hysteresis (4 points mapping)
void calibrateFullHysteresis360(uint32_t stepsPerRevolutionOfMotor);

// Is motor currently moving (for API)
bool isMotorMoving();
