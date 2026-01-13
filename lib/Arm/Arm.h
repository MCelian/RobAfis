#ifndef ARM_H
#define ARM_H

#include "Motor.h"

#define PWM 200
#define NO_MOVE_THRESHOLD 40
#define INITIALIZE_MAX_DURATION_MS 30000
#define STOP_MAX_DURATION_MS 500

class Arm {
public:
    Arm(Motor* motor) {
        _motor = motor;
    }

    void initialize() {
        _motor->moveUntilStall(PWM, NO_MOVE_THRESHOLD, INITIALIZE_MAX_DURATION_MS);
        Serial.println("ZERO FOUND");
        _motor->moveUntilStall(PWM, -1, 1700);
        Serial.println("END OFFSET");
        _motor->setCurrentPositionAsZero();
        _motor->moveUntilStall(-PWM, -1, 3000);
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

    void moveToGrabPosition() {
        _motor->moveToPosition(0, PWM);
    }

    void moveArmToNeutralPosition() {
        _motor->moveUntilStall(-PWM, -1, 3000);
    }
private:
    Motor* _motor;
    int _steerNegativeLimit;
    int _steerPositiveLimit;
    int _grabPosition;
};

#endif