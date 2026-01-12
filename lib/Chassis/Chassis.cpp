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
    _motorSteering->moveUntilStall(150, 1, 10000);
    _motorSteering->setCurrentPositionAsZero(); // This is now 0 (Right Limit)

    // 2. Move LEFT
    Serial.println("Finding Left Limit...");
    long totalWidthRaw = _motorSteering->moveUntilStall(-150, 5, 10000);

    // Setup PID for the final move
    long halfWidth = totalWidthRaw / 2;
    _motorSteering->moveToPosition(halfWidth, 150);

    // Final Zeroing
    _motorSteering->setCurrentPositionAsZero();
    _motorSteering->moveToPosition(0, 0);

    long range = abs(totalWidthRaw / 2);

    _steerRightLimit = range;
    _steerLeftLimit = -range;

    Serial.print("New Left Limit: "); Serial.println(_steerLeftLimit);
    Serial.print("New Right Limit: "); Serial.println(_steerRightLimit);

    Serial.println("PERFECT ZERO!");

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