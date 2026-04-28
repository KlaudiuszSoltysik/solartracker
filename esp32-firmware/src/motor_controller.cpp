#include <Arduino.h>
#include <AccelStepper.h>
#include "config.h"
#include "motor_controller.h"

// Initialize object of motor (type: DRIVER for TB6600: STEP + DIR)
AccelStepper stepper(AccelStepper::DRIVER, PIN_MOTOR_STEP, PIN_MOTOR_DIR);

void initMotor() {
    // Config ENABLE PIN
    pinMode(PIN_MOTOR_ENA, OUTPUT);
    digitalWrite(PIN_MOTOR_ENA, LOW); // Low state ENABLE movement

    // Limit switch configuration (internal Pull-Up resistor)
    pinMode(PIN_LIMIT_LEFT, INPUT_PULLUP);
    pinMode(PIN_LIMIT_RIGHT, INPUT_PULLUP);

    // Movement parameters
    stepper.setMaxSpeed(MOTOR_MAX_SPEED);
    stepper.setAcceleration(MOTOR_ACCEL);

    Serial.println("--- Motor initialized ---");
}

void handleMotor() {
    // 1. Check safety switches (limit switches)
    // We assume a pressed switch is pulled to ground (returns LOW)
    bool isLeftLimitHit = (digitalRead(PIN_LIMIT_LEFT) == LOW);
    bool isRightLimitHit = (digitalRead(PIN_LIMIT_RIGHT) == LOW);

    // If we're moving in one direction and hit the limit switch -> STOP
    // (distanceToGo < 0 means movement in one direction, > 0 in the other)
    if (isLeftLimitHit && stepper.distanceToGo() < 0) {
        stepper.stop();
        Serial.println("Left limit switch active!");
    }
    else if (isRightLimitHit && stepper.distanceToGo() > 0) {
        stepper.stop();
        Serial.println("Right limit switch active!");
    }

    // 2. Step the motor (if needed)
    stepper.run();
}


void moveMotorByAngle(float angle) {
    // 1. Calculate total motor steps for one full rotation (360 degrees) of the panel
    // Motor steps * microstepping * gearbox ratio
    float totalStepsForPanelRev = STEPS_PER_REV * MICROSTEPPING * GEAR_RATIO;

    // 2. Calculate steps per degree of panel rotation
    float stepsPerDegree = totalStepsForPanelRev / 360.0f;

    // 3. Calculate target step count for the requested angle
    long stepsToMove = angle * stepsPerDegree;

    // Command the movement to AccelStepper
    stepper.move(stepsToMove);

    Serial.printf("[MOTOR] Requested %.2f deg | Motor steps: %ld\n",
                  angle, stepsToMove);
}


void stopMotor() {
    stepper.stop();
    Serial.println("[MOTOR] Emergency stop!");
}

void moveMotorToHomePosition() {
    // Move in one direction until the limit switch is triggered
    // Assuming home position is at the left limit switch
    while (digitalRead(PIN_LIMIT_LEFT) == HIGH) { // While not at home position
        stepper.setSpeed(-MOTOR_MAX_SPEED / 4); // Move at quarter speed towards home
        stepper.runSpeed();
        yield(); 
    }
    stepper.stop(); // Stop when home position is reached
    // Optionally, move to current posistion - to be tested
    // stepper.moveTo(stepper.currentPosition()); 
    // stepper.run();

    // Reset the current position to zero after homing
    stepper.setCurrentPosition(0);
    // Move to a safe position (e.g., 5 degrees) after homing to avoid hitting the switch again
    moveMotorByAngle(5.0f); // Move 5 degrees away from home position
    while (stepper.distanceToGo() != 0) {
        stepper.run();
        yield();
    }
    Serial.println("[MOTOR] Moved to home position.");
}