#include "Motor.h"

Motor::Motor(int port) : _encoder(port) {
    _positionOffset = 0;
    _pulsePerDisc = 9;
    _lastRawPulse = 0;
    _noPulseCounter = 0;
}

int Motor::pulsesToDegrees(int pulses) {
    float ratio = getGearRatio();
    int pulseEnc = _pulsePerDisc > 0 ? _pulsePerDisc : 9;
    float degF = ((float)pulses / ( (float)pulseEnc * ratio )) * 360.0f;
    return (int)round(degF);
}

bool Motor::checkAndStopIfBlocked(int maxNoPulseIncrements) {
    int curr = getRawPulsePosition();

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