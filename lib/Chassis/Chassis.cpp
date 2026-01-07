#include "Chassis.h"
#include "Arduino.h"

Chassis::Chassis(int portAdvance, int portSteering) {
    _motorAdvance = new Motor(portAdvance);
    _motorSteering = new Motor(portSteering);
    float currentRatio = _motorSteering->getRatio();
    float newRatioF = currentRatio * GEAR_MULTIPLIER;
    _motorSteering->setRatio((int16_t)(newRatioF + 0.5f));

    _steerLeftLimit = 0;
    _steerRightLimit = 0;
}

Motor* tempMotor = nullptr;

static void updatePulseCount() {
    if (!tempMotor) return;
    if (digitalRead(tempMotor->getPortB()) == 0) {
        tempMotor->pulsePosMinus();
    } else {
        tempMotor->pulsePosPlus();
    }
}

long Chassis::steerToPosition(int position) {
    int pwmSign = (position - _motorSteering->getPosition()) >= 0 ? +1 : -1;
    int noMoveCount = 0;
    _motorSteering->update();
    long lastPos = _motorSteering->getPosition();

    tempMotor = _motorSteering;
    attachInterrupt(_motorSteering->getIntNum(), updatePulseCount, RISING);
    _motorSteering->setPwm(pwmSign * FIND_PWM);

    while (noMoveCount < NO_MOVE_THRESHOLD && abs(position - lastPos) >= MARGIN_STEER_POSITION) {
        _motorSteering->update();
        delay(SAMPLE_MS);
        long pos = _motorSteering->getPosition();
        if (abs(pos - lastPos) <= MARGIN_STEER_POSITION) {
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
    detachInterrupt(_motorSteering->getIntNum());
    tempMotor = nullptr;

    delay(50);
    return _motorSteering->getPosition();
};

void Chassis::findSteeringLimits() {
    leftPos = steerToPosition(-9999);
    long leftRaw = _motorSteering->getRawPulsePos();
    long leftDeg = _motorSteering->getPosition();
    long leftWheelDeg = _motorSteering->pulsesToDegrees(leftRaw);

    delay(150);

    rightPos = steerToPosition(+9999);
    long rightRaw = _motorSteering->getRawPulsePos();
    long rightDeg = _motorSteering->getPosition();
    long rightWheelDeg = _motorSteering->pulsesToDegrees(rightRaw);

    _steerLeftLimit = leftPos;
    _steerRightLimit = rightPos;

    long centerWheelDeg = (leftWheelDeg + rightWheelDeg) / 2;
    long currentRaw = _motorSteering->getRawPulsePos();
    long currentWheelDeg = _motorSteering->pulsesToDegrees(currentRaw);
    long currentPos = _motorSteering->getPosition();
    long centerTarget = currentPos + (centerWheelDeg - currentWheelDeg);

    steerToPosition(centerTarget);
}

    