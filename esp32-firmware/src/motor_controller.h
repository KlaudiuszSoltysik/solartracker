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