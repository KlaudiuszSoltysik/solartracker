#include <Arduino.h>
#include <AccelStepper.h>
#include "config.h"
#include "motor_controller.h"

// Initialize object of motor (type: DRIVER for A4988: STEP + DIR)
AccelStepper stepper(AccelStepper::DRIVER, PIN_MOTOR_STEP, PIN_MOTOR_DIR);

bool panelHomed = false;
bool motorFault = false;
float motorMinYawAngle = DEFAULT_MIN_YAW_ANGLE;
float motorMaxYawAngle = DEFAULT_MAX_YAW_ANGLE;

float calculatePanelAngleFromCurrentPosition()
{
    float totalStepsForPanelRev = STEPS_PER_REV * MICROSTEPPING * GEAR_RATIO;
    return HOME_POSITION_ANGLE + (((float)stepper.currentPosition() * MOTOR_DIRECTION_SIGN) / totalStepsForPanelRev) * 360.0f;
}

long angleToSteps(float angle)
{
    float totalStepsForPanelRev = STEPS_PER_REV * MICROSTEPPING * GEAR_RATIO;
    float stepsPerDegree = totalStepsForPanelRev / 360.0f;
    return angle * stepsPerDegree * MOTOR_DIRECTION_SIGN;
}

void setMotorFault(const char *message)
{
    motorFault = true;
    panelHomed = false;
    stepper.stop();
    digitalWrite(PIN_MOTOR_ENA, HIGH);
    Serial.printf("[MOTOR-FAULT] %s\n", message);
}

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

    if (isLeftLimitHit && isRightLimitHit)
    {
        setMotorFault("Both limit switches are active.");
        return;
    }

    if (panelHomed)
    {
        float currentAngle = calculatePanelAngleFromCurrentPosition();

        if (isLeftLimitHit && abs(currentAngle - motorMinYawAngle) > LIMIT_SWITCH_ANGLE_TOLERANCE)
        {
            setMotorFault("Left limit switch active outside expected angle range.");
            return;
        }

        if (isRightLimitHit && abs(currentAngle - motorMaxYawAngle) > LIMIT_SWITCH_ANGLE_TOLERANCE)
        {
            setMotorFault("Right limit switch active outside expected angle range.");
            return;
        }
    }

    long distanceToGo = stepper.distanceToGo();
    bool isMovingTowardLeftLimit = (HOME_DIRECTION_SIGN > 0) ? (distanceToGo > 0) : (distanceToGo < 0);
    bool isMovingTowardRightLimit = (HOME_DIRECTION_SIGN > 0) ? (distanceToGo < 0) : (distanceToGo > 0);

    // If we're moving toward an active limit switch -> STOP.
    if (isLeftLimitHit && isMovingTowardLeftLimit)
    {
        stepper.stop();
        Serial.println("Left limit switch active!");
    }
    else if (isRightLimitHit && isMovingTowardRightLimit)
    {
        stepper.stop();
        Serial.println("Right limit switch active!");
    }
if (stepper.distanceToGo() != 0)
    {
        if (digitalRead(PIN_MOTOR_ENA) == HIGH) 
        {
            digitalWrite(PIN_MOTOR_ENA, LOW);
            delay(10); // Short delay to ensure the motor driver is enabled before stepping
        }
    }

    // 2. Step the motor (if needed)
    stepper.run();

    // EcoMODE: If we have reached the target position, we can disable the coils to save energy and reduce heat
    if (stepper.distanceToGo() == 0 && digitalRead(PIN_MOTOR_ENA) == LOW)
    {
        digitalWrite(PIN_MOTOR_ENA, HIGH); 
        Serial.println("[MOTOR] Cel osiągnięty. Cewki odłączone (Eco Mode).");
    }
}

void moveMotorByAngle(float angle)
{
    if (motorFault)
    {
        Serial.println("[MOTOR] Move rejected: motor fault is active.");
        return;
    }

    if (!panelHomed)
    {
        Serial.println("[MOTOR] Move rejected: panel is not homed.");
        return;
    }

    long stepsToMove = angleToSteps(angle);

    // Command the movement to AccelStepper
    stepper.move(stepsToMove);

    Serial.printf("[MOTOR] Requested %.2f deg | Motor steps: %ld\n",
                  angle, stepsToMove);
}

void stopMotor()
{
    stepper.stop();
    panelHomed = false;
    motorFault = true;
    Serial.println("[MOTOR] Emergency stop!");
}

bool moveMotorToHomePosition()
{

     Serial.println("[MOTOR] Homing start. Enabling motor...");
    digitalWrite(PIN_MOTOR_ENA, LOW);
    delay(10);

    unsigned long homingStartedAt = millis();
    long startPosition = stepper.currentPosition();
    long maxHomingSteps = abs(angleToSteps(HOMING_MAX_TRAVEL_ANGLE));

    // Move in one direction until the limit switch is triggered
    // Assuming home position is at the left limit switch
    while (digitalRead(PIN_LIMIT_LEFT) == HIGH)
    {                                           // While not at home position
        if (millis() - homingStartedAt > HOMING_TIMEOUT_MS)
        {
            setMotorFault("Homing timeout before left limit switch.");
            return false;
        }

        if (abs(stepper.currentPosition() - startPosition) > maxHomingSteps)
        {
            setMotorFault("Homing exceeded max travel before left limit switch.");
            return false;
        }

        stepper.setSpeed(HOME_DIRECTION_SIGN * MOTOR_MAX_SPEED / 4); // Move at quarter speed towards home
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
    panelHomed = true;
    motorFault = false;
    // Move to a safe position after homing to avoid hitting the switch again
    moveMotorByAngle(7.2f); // Move 7.2 degrees away from home position
    while (stepper.distanceToGo() != 0)
    {
        if (millis() - homingStartedAt > HOMING_TIMEOUT_MS)
        {
            setMotorFault("Homing timeout while moving away from limit switch.");
            return false;
        }

        stepper.run();
        yield();
    }
    digitalWrite(PIN_MOTOR_ENA, HIGH);
    Serial.println("[MOTOR] Moved to home position.");
    return true; // Indicate successful homing
}

float getCurrentPanelAngle()
{
    return calculatePanelAngleFromCurrentPosition();
}

YawRange calibrateYawRange()
{
    Serial.println("\n=== YAW RANGE CALIBRATION START ===");
    Serial.println("[YAW-CAL] Moving to left limit switch...");
    digitalWrite(PIN_MOTOR_ENA, LOW);
    delay(10);

    unsigned long calibrationStartedAt = millis();
    long startPosition = stepper.currentPosition();
    long maxCalibrationSteps = abs(angleToSteps(HOMING_MAX_TRAVEL_ANGLE));

    while (digitalRead(PIN_LIMIT_LEFT) == HIGH)
    {
        if (millis() - calibrationStartedAt > HOMING_TIMEOUT_MS)
        {
            setMotorFault("Calibration timeout before left limit switch.");
            return {};
        }

        if (abs(stepper.currentPosition() - startPosition) > maxCalibrationSteps)
        {
            setMotorFault("Calibration exceeded max travel before left limit switch.");
            return {};
        }

        stepper.setSpeed(HOME_DIRECTION_SIGN * MOTOR_MAX_SPEED / 4);
        stepper.runSpeed();
        yield();
    }

    stepper.stop();
    stepper.setCurrentPosition(0);
    panelHomed = true;
    motorFault = false;

    Serial.println("[YAW-CAL] Left limit reached. Position set to 0 steps.");
    delay(1000);

    Serial.println("[YAW-CAL] Moving to right limit switch...");
    calibrationStartedAt = millis();
    startPosition = stepper.currentPosition();

    while (digitalRead(PIN_LIMIT_RIGHT) == HIGH)
    {
        if (millis() - calibrationStartedAt > HOMING_TIMEOUT_MS)
        {
            setMotorFault("Calibration timeout before right limit switch.");
            return {};
        }

        if (abs(stepper.currentPosition() - startPosition) > maxCalibrationSteps)
        {
            setMotorFault("Calibration exceeded max travel before right limit switch.");
            return {};
        }

        stepper.setSpeed(-HOME_DIRECTION_SIGN * MOTOR_MAX_SPEED / 4);
        stepper.runSpeed();
        yield();
    }

    stepper.stop();
    digitalWrite(PIN_MOTOR_ENA, HIGH);
    long maxSteps = abs(stepper.currentPosition());
    float totalStepsForPanelRev = STEPS_PER_REV * MICROSTEPPING * GEAR_RATIO;
    float rangeAngle = ((float)maxSteps / totalStepsForPanelRev) * 360.0f;

    YawRange range;
    range.minSteps = 0;
    range.maxSteps = maxSteps;
    range.minAngle = HOME_POSITION_ANGLE;
    range.maxAngle = HOME_POSITION_ANGLE + rangeAngle;
    range.rangeAngle = rangeAngle;

    Serial.println("\n=== YAW RANGE CALIBRATION RESULT ===");
    Serial.printf("Min steps   : %ld\n", range.minSteps);
    Serial.printf("Max steps   : %ld\n", range.maxSteps);
    Serial.printf("Min angle   : %.2f deg\n", range.minAngle);
    Serial.printf("Max angle   : %.2f deg\n", range.maxAngle);
    Serial.printf("Range angle : %.2f deg\n", range.rangeAngle);
    Serial.println("====================================\n");

    return range;
}

bool isPanelHomed()
{
    return panelHomed;
}

bool hasMotorFault()
{
    return motorFault;
}

void clearMotorFault()
{
    motorFault = false;
}

void setMotorAngleLimits(float minAngle, float maxAngle)
{
    motorMinYawAngle = minAngle;
    motorMaxYawAngle = maxAngle;
}

const char *getMotorStatus()
{
    if (motorFault)
        return "MOTOR_FAULT";

    if (!panelHomed)
        return "NOT_HOMED";

    if (isMotorMoving())
        return "MOVING";

    return "OK";
}

void calibrateFullHysteresis360(uint32_t stepsPerRevolutionOfMotor)
{
    Serial.println("\n=== Hysteresis mapping start ===");
    digitalWrite(PIN_MOTOR_ENA, LOW);
    delay(10);

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
    digitalWrite(PIN_MOTOR_ENA, HIGH);
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
    return stepper.distanceToGo() != 0;
}
