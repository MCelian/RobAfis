#ifndef MOTOR_H
#define MOTOR_H

#include "MeEncoderOnBoard.h"

class Motor {
public:
    Motor(int port);

    int getInterruptionNumber() { return _encoder.getIntNum(); }
    int getPulsePosition() { return _encoder.getCurPos() - _positionOffset; }
    int getRawPulsePosition() { return _encoder.getPulsePos(); }
    float getGearRatio() { return _encoder.getRatio(); }

    int getPortB() { return _encoder.getPortB(); }

    void setCurrentPosition(int position) { _positionOffset = _encoder.getCurPos() - position; }
    void setPwm(int pwm) { _encoder.setMotorPwm(pwm); }
    void setPulse(int pulseCount) { _encoder.setPulse(pulseCount); _pulsePerDisc = pulseCount; }

    void setGearRatio(float ratio) { _encoder.setRatio(ratio); }

    void pulsePositionIncrement() { _encoder.pulsePosPlus(); }
    void pulsePositionDecrement() { _encoder.pulsePosMinus(); }
    void stop() { _encoder.setMotorPwm(0); }
    void updateEncoderValue() { _encoder.loop(); }

    bool checkAndStopIfBlocked(int noMoveThreshold);
    int pulsesToDegrees(int pulses);

private:
    MeEncoderOnBoard _encoder;
    int _pulsePerDisc;
    int _positionOffset;
    int _lastRawPulse;
    int _noPulseCounter;
};

#endif
