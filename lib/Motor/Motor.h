#ifndef MOTOR_H
#define MOTOR_H

#include "MeEncoderOnBoard.h" // Only the specific driver

class Motor {
public:
    Motor(int port);
    void setPwm(int pwm);
    void update();
    int getPosition(); 
    void setCurrentPosition(int pos);
    int getRawPulsePos();
    int getIntNum();
    void pulsePosPlus();
    void pulsePosMinus();
    void stop();
    int getPortB();
    void setRatio(float ratio);
    void setPulse(int pulseCount);
    float getRatio();
    bool checkAndStopIfBlocked(int noMoveThreshold);
    int pulsesToDegrees(int pulses);

private:
    MeEncoderOnBoard _encoder;
    int _positionOffset;
    int _pulsePerDisc;
    int _lastRawPulse;
    int _noPulseCounter;
};

#endif