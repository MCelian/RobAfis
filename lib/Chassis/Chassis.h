#ifndef CHASSIS_H
#define CHASSIS_H

#include "Motor.h"

class Chassis {
public:
    Chassis(Motor* motorAdvance, Motor* motorSteering);
    void forward();
    void backward();
    void turn_left();
    void turn_right();
    void stop_movement();
    void stop_steering();

private:
    friend class Robot;
    Motor* _motor_advance;
    Motor* _motor_steering;
};

#endif
