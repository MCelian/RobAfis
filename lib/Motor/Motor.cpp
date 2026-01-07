#include "Motor.h"

Motor::Motor(int port) : _encoder(port) {
    _positionOffset = 0;
    _pulsePerDisc = 9;
    _lastRawPulse = 0;
    _noPulseCounter = 0;
}

void Motor::stop() {
    _encoder.setMotorPwm(0);
}

void Motor::setPwm(int pwm) {
    _encoder.setMotorPwm(pwm);
}

void Motor::update() {
    _encoder.loop();
}

int Motor::getIntNum() {
    return _encoder.getIntNum();
}

int Motor::getPortB() {
    return _encoder.getPortB();
}

int Motor::getPosition() {
    int rawPos = _encoder.getCurPos();
    
    return rawPos - _positionOffset; 
}

void Motor::setCurrentPosition(int pos) {
    int rawPos = _encoder.getCurPos();

    _positionOffset = rawPos - pos;
}

int Motor::getRawPulsePos() {
    return _encoder.getPulsePos();
}

void Motor::pulsePosPlus() {
    _encoder.pulsePosPlus();
}

void Motor::pulsePosMinus() {
    _encoder.pulsePosMinus();
}

void Motor::setRatio(float ratio) {
    _encoder.setRatio(ratio);
}

void Motor::setPulse(int pulseCount) {
    _encoder.setPulse(pulseCount);
    _pulsePerDisc = pulseCount;
}

float Motor::getRatio() {
    return _encoder.getRatio();
}

int Motor::pulsesToDegrees(int pulses) {
    float ratio = getRatio();
    int pulseEnc = _pulsePerDisc > 0 ? _pulsePerDisc : 9;
    float degF = ((float)pulses / ( (float)pulseEnc * ratio )) * 360.0f;
    return (int)round(degF);
}

bool Motor::checkAndStopIfBlocked(int maxNoPulseIncrements) {
    int curr = getRawPulsePos();
    if (curr == _lastRawPulse) {
        _noPulseCounter++;
    } else {
        _noPulseCounter = 0;
        _lastRawPulse = curr;
    }

    if (_noPulseCounter > maxNoPulseIncrements) {
        stop();
        return true;
    }
    return false;
}