#ifndef ARM_H
#define ARM_H

#include "Motor.h"

#define PWM 255
#define NO_MOVE_THRESHOLD 10
#define INITIALIZE_MAX_DURATION_MS 100000
#define STOP_MAX_DURATION_MS 500

class Arm {
public:
    Arm(Motor* motor) {
        _motor = motor;
    }

    void initialize() {
        _motor->moveUntilStall(PWM, NO_MOVE_THRESHOLD, INITIALIZE_MAX_DURATION_MS);
    }

    void turnPositiveDuringMs(int durationMs, bool (*stopCondition)() = nullptr) {
        _motor->moveUntilStall(PWM, NO_MOVE_THRESHOLD, durationMs, stopCondition);
    }

    void turnNegativeDuringMs(int durationMs, bool (*stopCondition)() = nullptr) {
        _motor->moveUntilStall(-PWM, NO_MOVE_THRESHOLD, durationMs, stopCondition);
    }

    void stop() {
        _motor->moveUntilStall(0, 0, STOP_MAX_DURATION_MS);
    }

    void moveToGrabPosition() {}
private:
    Motor* _motor;
    int _steerNegativeLimit;
    int _steerPositiveLimit;
    int _grabPosition;
};

#endif