#ifndef CHASSIS_H
#define CHASSIS_H

#include "Motor.h"

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

    void steerToAngle(int angle) {
        _motorSteering->moveToPosition(angle, 0);
    };

    void advanceForwardDuringMs(int durationMs, bool (*stopCondition)() = nullptr) {
        _motorAdvance->moveUntilStall(+100, 100, durationMs, stopCondition);
    };

    void advanceBackwardDuringMs(int durationMs, bool (*stopCondition)() = nullptr) {
        _motorAdvance->moveUntilStall(-100, 100, durationMs, stopCondition);
    };

    void advanceStop() {
        _motorAdvance->moveUntilStall(0, 100, 10000);
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
