#include "Chassis.h"

Chassis::Chassis(Motor* motorAdvance, Motor* motorSteering) {
    _motorAdvance = motorAdvance;
    _motorSteering = motorSteering;
}

void Chassis::initialize() {
    if (_motorSteering == nullptr || _motorAdvance == nullptr) {
        Serial.println("ERROR: Motors not linked!");
        return;
    }

    _motorSteering->moveUntilStall(STEER_PWM, MOTOR_MIN_PULSES, STEER_CALIBRATION_TIMEOUT_MS);
    _motorSteering->setCurrentPositionAsZero();

    long totalWidthRaw = _motorSteering->moveUntilStall(-STEER_PWM, MOTOR_MIN_PULSES, STEER_CALIBRATION_TIMEOUT_MS);

    long halfWidth = totalWidthRaw / 2;
    _motorSteering->moveToPosition(halfWidth, STEER_PWM);

    _motorSteering->setCurrentPositionAsZero();
    _motorSteering->moveToPosition(0, 0);

    long range = abs(totalWidthRaw / 2);

    _steerRightLimit = range;
    _steerLeftLimit = -range;

    _isInitialized = true;
}

void Chassis::pivotLookLeft() {
    // To point NOSE Left, we must steer RIGHT and reverse
    steerToLeftLimit();
}

void Chassis::pivotLookRight() {
    // To point NOSE Right, we must steer LEFT and reverse
    steerToRightLimit();
}