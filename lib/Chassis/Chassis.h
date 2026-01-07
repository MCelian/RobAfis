#ifndef CHASSIS_H
#define CHASSIS_H

#include "Motor.h"
#define FIND_PWM 255
#define SAMPLE_MS 50
#define NO_MOVE_THRESHOLD 10
#define MARGIN_STEER_POSITION 5
#define GEAR_MULTIPLIER 72.0f / 8.0f

class Chassis {
public:
    Chassis(int portAdvance, int portSteering);
    void findSteeringLimits();

private:
    Motor* _motorAdvance;
    Motor* _motorSteering;
    long _steerLeftLimit;
    long _steerRightLimit;
    long steerUntilStop(int pwmSign);
    long steerToPosition(int position);

public:
    long leftPos = 0;
    long rightPos = 0;

};

#endif
