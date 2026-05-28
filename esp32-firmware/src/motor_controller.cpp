#include <Arduino.h>
#include <AccelStepper.h>
#include "config.h"
#include "motor_controller.h"

// Initialize object of motor (type: DRIVER for TB6600: STEP + DIR)
AccelStepper stepper(AccelStepper::DRIVER, PIN_MOTOR_STEP, PIN_MOTOR_DIR);

void initMotor()
{
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

void handleMotor()
{
    // 1. Check safety switches (limit switches)
    // We assume a pressed switch is pulled to ground (returns LOW)
    bool isLeftLimitHit = (digitalRead(PIN_LIMIT_LEFT) == LOW);
    bool isRightLimitHit = (digitalRead(PIN_LIMIT_RIGHT) == LOW);

    // If we're moving in one direction and hit the limit switch -> STOP
    // (distanceToGo < 0 means movement in one direction, > 0 in the other)
    if (isLeftLimitHit && stepper.distanceToGo() < 0)
    {
        stepper.stop();
        Serial.println("Left limit switch active!");
    }
    else if (isRightLimitHit && stepper.distanceToGo() > 0)
    {
        stepper.stop();
        Serial.println("Right limit switch active!");
    }

    // 2. Step the motor (if needed)
    stepper.run();
}

void moveMotorByAngle(float angle)
{
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

void stopMotor()
{
    stepper.stop();
    Serial.println("[MOTOR] Emergency stop!");
}

bool moveMotorToHomePosition()
{
    // Move in one direction until the limit switch is triggered
    // Assuming home position is at the left limit switch
    while (digitalRead(PIN_LIMIT_LEFT) == HIGH)
    {                                           // While not at home position
        stepper.setSpeed(-MOTOR_MAX_SPEED / 4); // Move at quarter speed towards home
        stepper.runSpeed();
        yield();
    }
    //stepper.stop(); // Stop when home position is reached
    // Optionally, move to current posistion - to be tested
     stepper.moveTo(stepper.currentPosition());
     stepper.run();
    vTaskDelay(1000);
    // Reset the current position to zero after homing
    stepper.setCurrentPosition(0);
    // Move to a safe position after homing to avoid hitting the switch again
    moveMotorByAngle(7.2f); // Move 7.2 degrees away from home position
    while (stepper.distanceToGo() != 0)
    {
        stepper.run();
        yield();
    }
    Serial.println("[MOTOR] Moved to home position.");
    return true; // Indicate successful homing
}

float getCurrentPanelAngle()
{
    // Calculate total motor steps for one full rotation (360 degrees) of the panel
    float totalStepsForPanelRev = STEPS_PER_REV * MICROSTEPPING * GEAR_RATIO;

    // Calculate current angle based on AccelStepper position and configured home angle.
    float currentAngle = HOME_POSITION_ANGLE + ((float)stepper.currentPosition() / totalStepsForPanelRev) * 360.0f;

    return currentAngle;
}

void calibrateFullHysteresis360(uint32_t stepsPerRevolutionOfMotor)
{
    Serial.println("\n=== Hysteresis mapping start ===");

    // P1 - left trigger edge
    while (digitalRead(PIN_LIMIT_LEFT) == HIGH) {
        stepper.setSpeed(-MOTOR_MAX_SPEED / 4);
        stepper.runSpeed();
        yield();
    }

    stepper.stop();
    while (stepper.distanceToGo() != 0) {
        stepper.run();
        yield();
    }

    stepper.setCurrentPosition(0);

    int32_t P1 = 0;
    delay(1000);

    // P2 - left release edge
    while (digitalRead(PIN_LIMIT_LEFT) == LOW) {
        stepper.setSpeed(-MOTOR_MAX_SPEED / 10);
        stepper.runSpeed();
        yield();
    }

    stepper.stop();
    while (stepper.distanceToGo() != 0) {
        stepper.run();
        yield();
    }

    int32_t P2 = stepper.currentPosition();
    delay(1000);

    // P3 - right trigger edge
    while (digitalRead(PIN_LIMIT_LEFT) == HIGH) {
        stepper.setSpeed(MOTOR_MAX_SPEED / 10);
        stepper.runSpeed();
        yield();
    }

    stepper.stop();
    while (stepper.distanceToGo() != 0) {
        stepper.run();
        yield();
    }

    int32_t P3 = stepper.currentPosition();
    delay(1000);

    // P4 - right release edge
    while (digitalRead(PIN_LIMIT_LEFT) == LOW) {
        stepper.setSpeed(MOTOR_MAX_SPEED / 10);
        stepper.runSpeed();
        yield();
    }

    stepper.stop();
    while (stepper.distanceToGo() != 0) {
        stepper.run();
        yield();
    }

    int32_t P4 = stepper.currentPosition();

    float initialCenter = (float)(P1 + P3) / 2.0f;

    Serial.println("\n--- Initial mapping done ---");
    Serial.printf("P1: %d\n", P1);
    Serial.printf("P2: %d\n", P2);
    Serial.printf("P3: %d\n", P3);
    Serial.printf("P4: %d\n", P4);
    Serial.printf("Left width : %d steps\n", abs(P1 - P2));
    Serial.printf("Right width: %d steps\n", abs(P3 - P4));
    Serial.printf("Center     : %.1f\n", initialCenter);

    delay(2000);

    // Full 360 rotation
    while (digitalRead(PIN_LIMIT_LEFT) == HIGH) {
        stepper.setSpeed(MOTOR_MAX_SPEED / 4);
        stepper.runSpeed();
        yield();
    }

    stepper.stop();
    while (stepper.distanceToGo() != 0) {
        stepper.run();
        yield();
    }

    int32_t P1_next = stepper.currentPosition();
    delay(1000);

    while (digitalRead(PIN_LIMIT_LEFT) == LOW) {
        stepper.setSpeed(MOTOR_MAX_SPEED / 10);
        stepper.runSpeed();
        yield();
    }

    stepper.stop();
    while (stepper.distanceToGo() != 0) {
        stepper.run();
        yield();
    }

    int32_t P2_next = stepper.currentPosition();

    float finalCenter = (float)(P1_next + P2_next) / 2.0f;
    float hysteresisOffset = (float)abs(P3 - P1);

    float trueStepsFor360 =
        finalCenter - initialCenter + hysteresisOffset;

    float realGearRatio =
        trueStepsFor360 / (float)stepsPerRevolutionOfMotor;

    Serial.println("\n===========================================");
    Serial.println("              FINAL REPORT");
    Serial.println("===========================================");

    Serial.printf("P1_next           : %d\n", P1_next);
    Serial.printf("P2_next           : %d\n", P2_next);
    Serial.printf("Final center      : %.1f\n", finalCenter);
    Serial.printf("Hysteresis offset : %.1f\n", hysteresisOffset);

    Serial.println("-------------------------------------------");

    Serial.printf("Steps per 360 deg : %.0f\n", trueStepsFor360);
    Serial.printf("Gear ratio        : %.5f\n", realGearRatio);

    Serial.println("===========================================");
}

bool isMotorMoving()
{
    return stepper.isRunning();
}