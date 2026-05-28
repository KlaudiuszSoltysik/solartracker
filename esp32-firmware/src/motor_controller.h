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

// Calibration of hysteresis (4 points mapping)
void calibrateFullHysteresis360(uint32_t stepsPerRevolutionOfMotor);

// Is motor currently moving (for API)
bool isMotorMoving();