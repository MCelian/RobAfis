#ifndef CHASSIS_H
#define CHASSIS_H

#include "Motor.h"

class Chassis {
public:
    Chassis(Motor* motorAdvance, Motor* motorSteering);
    void forward();
    void backward();
    void align_left();
    void align_right();
    void align_center();
    void stop_movement();
    void stop_steering();
    void update_motors();
    void save_steering_pos();
    
    Motor* getMotorAdvance() { return _motor_advance; };
    Motor* getMotorSteering() { return _motor_steering; };

private:
    friend class Robot;
    Motor* _motor_advance;
    Motor* _motor_steering;
};

#endif
