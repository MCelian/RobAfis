#include "Chassis.h"

Chassis::Chassis(Motor* motorAdvance, Motor* motorSteering) {
    _motorAdvance = motorAdvance;
    _motorSteering = motorSteering;
}

void Chassis::initialize() {
    // Now this check is safe
    if (_motorSteering == nullptr || _motorAdvance == nullptr) {
        Serial.println("ERROR: Motors not linked!");
        return;
    }

    Serial.println("--- STARTING ---");

    Serial.println("Finding Right Limit...");
    _motorSteering->moveUntilStall(150, 5, 100000);
    _motorSteering->setCurrentPositionAsZero();

    Serial.println("Finding Left Limit...");
    long totalWidthRaw = _motorSteering->moveUntilStall(-150, 5, 10000);

    long halfWidth = totalWidthRaw / 2;
    _motorSteering->moveToPosition(halfWidth, 150);

    _motorSteering->setCurrentPositionAsZero();
    _motorSteering->moveToPosition(0, 0);

    long range = abs(totalWidthRaw / 2);

    _steerRightLimit = range;
    _steerLeftLimit = -range;

    Serial.print("New Left Limit: "); Serial.println(_steerLeftLimit);
    Serial.print("New Right Limit: "); Serial.println(_steerRightLimit);

    Serial.println("PERFECT ZERO!");

    advanceForwardDuringMs(1000);
    _isInitialized = true;
}

void Chassis::pivotLookLeft() {
    // To point NOSE Left, we must steer RIGHT and reverse
    steerToLeftLimit();
    advanceBackwardDuringMs(600);
}

void Chassis::pivotLookRight() {
    // To point NOSE Right, we must steer LEFT and reverse
    steerToLeftLimit();
    advanceBackwardDuringMs(600);
}