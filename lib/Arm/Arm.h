#ifndef ARM_H
#define ARM_H

#include "Motor.h"

#define INITIALIZE_PWM 255
#define NORMAL_PWM 200
#define NO_MOVE_THRESHOLD 5
#define INITIALIZE_MAX_DURATION_MS 10000
#define STOP_MAX_DURATION_MS 500

class Arm {
public:
    Arm(Motor* motor) {
        _motor = motor;
    }

    void initialize() {
        Serial.println("START");
        _motor->moveUntilStall(+INITIALIZE_PWM, NO_MOVE_THRESHOLD, INITIALIZE_MAX_DURATION_MS);
    }

    void turnPositiveDuringMs(int durationMs, bool (*stopCondition)() = nullptr) {
        _motor->moveUntilStall(NORMAL_PWM, NO_MOVE_THRESHOLD, durationMs, stopCondition);
    }

    void turnNegativeDuringMs(int durationMs, bool (*stopCondition)() = nullptr) {
        _motor->moveUntilStall(-NORMAL_PWM, NO_MOVE_THRESHOLD, durationMs, stopCondition);
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