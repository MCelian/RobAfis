#ifndef ARM_H
#define ARM_H

#include "Motor.h"

#define SPEED 255
#define NO_MOVE_THRESHOLD 5

class Arm {
public:
    Arm(Motor* motor);
    void initialize();

    void turnPositive(bool (*stopCondition)() = nullptr) {
        _motor->moveUntilStall(200, 100, 10000, stopCondition);
    };

    void turnNegative(bool (*stopCondition)() = nullptr) {
        _motor->moveUntilStall(-100, 100, 10000, stopCondition);
    };

    void stop() {
        _motor->moveUntilStall(0, 100, 10000);
    };

    void moveToGrabPosition() {}
private:
    Motor* _motor;
    int _steerNegativeLimit;
    int _steerPositiveLimit;
    int _grabPosition;
};

#endif