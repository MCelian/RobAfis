#ifndef ARM_H
#define ARM_H

#include "Motor.h"

#define SPEED 255
#define NO_MOVE_THRESHOLD 5

class Arm {
public:
    Arm(Motor* motor) {
        _motor = motor;
    }

    void initialize() {
        Serial.println("START");
        _motor->moveUntilStall(250, 5, 2000);
    };

    void turnPositiveDuringMs(int durationMs, bool (*stopCondition)() = nullptr) {
        _motor->moveUntilStall(200, 5, durationMs, stopCondition);
    };

    void turnNegativeDuringMs(int durationMs, bool (*stopCondition)() = nullptr) {
        _motor->moveUntilStall(-200, 5, durationMs, stopCondition);
    };

    void stop() {
        _motor->moveUntilStall(0, 0, 500);
    };

    void moveToGrabPosition() {}
private:
    Motor* _motor;
    int _steerNegativeLimit;
    int _steerPositiveLimit;
    int _grabPosition;
};

#endif