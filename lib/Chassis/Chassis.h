#ifndef CHASSIS_H
#define CHASSIS_H

#include "Motor.h"

#define MOTOR_MIN_PULSES 2

#define STEER_PWM 200
#define STEER_CALIBRATION_TIMEOUT_MS 100000

#define ADVANCE_PWM 250

#define STOP_DURATION_MS 500

class Chassis {
public:
    Chassis(Motor* motorAdvance, Motor* motorSteering);
    void initialize();
    void steerToLeftLimit() {
        _motorSteering->moveToPosition(_steerLeftLimit, 0);
    }

    void steerToRightLimit() {
        _motorSteering->moveToPosition(_steerRightLimit, 0);
    }

    void steerToCenter() {
        _motorSteering->moveToPosition(0, 0);
    };

    void advanceForwardDuringMs(int durationMs, bool (*stopCondition)() = nullptr) {
        _motorAdvance->moveUntilStall(-ADVANCE_PWM, MOTOR_MIN_PULSES, durationMs, stopCondition);
    };

    void advanceBackwardDuringMs(int durationMs, bool (*stopCondition)() = nullptr) {
        _motorAdvance->moveUntilStall(+ADVANCE_PWM, MOTOR_MIN_PULSES, durationMs, stopCondition);
    };

    void advanceStop() {
        _motorAdvance->moveUntilStall(0, MOTOR_MIN_PULSES, STOP_DURATION_MS);
    };

    void pivotLookLeft();

    void pivotLookRight();
private:
    Motor* _motorAdvance = nullptr;
    Motor* _motorSteering = nullptr;
    int _isInitialized = false;
    int _steerLeftLimit = 0;
    int _steerRightLimit = 0;
    int _centerPosition = 0;
};

#endif
