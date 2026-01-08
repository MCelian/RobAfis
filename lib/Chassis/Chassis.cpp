#include "Chassis.h"
#include "Arduino.h"

Motor* tempMotor = nullptr;
static void updatePulseCount() {
    if (!tempMotor) return;
    if (digitalRead(tempMotor->getPortB()) == 0) {
        tempMotor->pulsePositionDecrement();
    } else {
        tempMotor->pulsePositionIncrement();
    }
}

Chassis::Chassis(int portAdvance, int portSteering) {
    _motorAdvance = new Motor(portAdvance);
    _motorSteering = new Motor(portSteering);
    float currentRatio = _motorSteering->getGearRatio();
    float newRatio = currentRatio * GEAR_MULTIPLIER;
    _motorSteering->setGearRatio((int)(newRatio + 0.5f));

    _steerLeftLimit = 0;
    _steerRightLimit = 0;
}

void Chassis::steerToPosition(int position) {
    _motorSteering->stop();
    int pwmSign = (position - _motorSteering->getPulsePosition()) >= 0 ? +1 : -1;

    int noMoveCount = 0;
    _motorSteering->updateEncoderValue();
    int lastPos = _motorSteering->getPulsePosition();

    tempMotor = _motorSteering;
    attachInterrupt(_motorSteering->getInterruptionNumber(), updatePulseCount, RISING);
    _motorSteering->setPwm(pwmSign * FIND_PWM);

    while (noMoveCount < NO_MOVE_THRESHOLD && abs(position - lastPos) >= MARGIN_STEER_POSITION) {
        _motorSteering->updateEncoderValue();
        delay(SAMPLE_MS);
        long pos = _motorSteering->getPulsePosition();
        int delta = abs(pos - lastPos);

        if (delta <= MARGIN_STEER_POSITION) {
            noMoveCount++;
        } else {
            noMoveCount = 0;
            lastPos = pos;
        }

        if (_motorSteering->checkAndStopIfBlocked(NO_MOVE_THRESHOLD)) {
            break;
        }
    }
    _motorSteering->stop();
    detachInterrupt(_motorSteering->getInterruptionNumber());
    tempMotor = nullptr;

    delay(50);
};

void Chassis::findSteeringLimits() {
    _motorSteering->stop();
    steerToPosition(-9999);
    _motorSteering->stop();

    int leftPulsePos = _motorSteering->getPulsePosition();
    setSteerLeftLimit(leftPulsePos);

    int leftRaw = _motorSteering->getRawPulsePosition();
    int leftWheelDeg = _motorSteering->pulsesToDegrees(leftRaw);

    delay(150);

    steerToPosition(+9999);
    _motorSteering->stop();
    int rightPulsePos = _motorSteering->getPulsePosition();
    setSteerRightLimit(rightPulsePos);

    int rightRaw = _motorSteering->getRawPulsePosition();
    int rightWheelDeg = _motorSteering->pulsesToDegrees(rightRaw);

    float centerWheelDeg = (leftWheelDeg + rightWheelDeg) / 2.0f;
    setCenterWheelDeg(centerWheelDeg);
    _motorSteering->stop();
    
    float centerOffset = getCenterWheelDeg() - getCurrentWheelDeg();
    float newCenterPos = getCurrentPosition() + centerOffset;
    setCenterPosition(newCenterPos);

    steerCenter();
    _motorSteering->stop();
}

void Chassis::steerUntilStop(int pwmSign) {
    steerToPosition(pwmSign * 9999);
    setCurrentRaw(_motorSteering->getRawPulsePosition());
    setCurrentWheelDeg(_motorSteering->pulsesToDegrees(getCurrentRaw()));
    setCurrentRaw(_motorSteering->getRawPulsePosition());
    setCurrentWheelDeg(_motorSteering->pulsesToDegrees(getCurrentRaw()));
}

void Chassis::steerLeft() {
    steerToPosition(getSteerLeftLimit() + 15);
}

void Chassis::steerRight() {
    steerToPosition(getSteerRightLimit() - 15);
}

void Chassis::steerCenter() {
    steerToPosition(getCenterPosition());
}

void Chassis::advanceForward() {
    _motorAdvance->setPwm(-ADVANCE_SPEED);
}

void Chassis::advanceBackward() {
    _motorAdvance->setPwm(ADVANCE_SPEED);
}

void Chassis::advanceStop() {
    _motorAdvance->setPwm(0);
}

void Chassis::waitAndKeepAlive(unsigned long ms) {
    unsigned long start = millis();
    while (millis() - start < ms) {
        // Keep the PID loops alive!
        _motorAdvance->updateEncoderValue();
        _motorSteering->updateEncoderValue();
        delay(5); // Short delay to save CPU
    }
}