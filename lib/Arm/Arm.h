#ifndef ARM_H
#define ARM_H

#include "Motor.h"

#define SPEED 255
#define NO_MOVE_THRESHOLD 5

class Arm {
public:
    Arm(int port) { _motor = new Motor(port); }
    void raise() { _motor->setPwm(SPEED); }
    void lower() { _motor->setPwm(-SPEED); }
    void stop() { _motor->setPwm(0); };
    void initialize();
    void moveToGrabPosition();
private:
    Motor* _motor;
    int _steerLeftLimit;
    int _steerRightLimit;
    int _centerWheelDeg = 0;
    int _currentRaw = 0;
    int _currentWheelDeg = 0;
    int _currentPostion = 0;
    int _centerPosition = 0;
};

#endif