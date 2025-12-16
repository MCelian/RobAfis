#include "Chassis.h"
#include "Motor.h"

#define MAX_SPEED 255
#define STOP_SPEED 0
    
Chassis::Chassis(Motor* motor_advance, Motor* motor_steering)
{
    _motor_advance = motor_advance;
    _motor_steering = motor_steering;
}

void Chassis::forward() {
    _motor_advance->set_analogic_speed(MAX_SPEED);
}

void Chassis::backward() {
    _motor_advance->set_analogic_speed(-MAX_SPEED);
}

void Chassis::turn_left() {
    _motor_steering->set_analogic_speed(MAX_SPEED);
}

void Chassis::turn_right() {
    _motor_steering->set_analogic_speed(-MAX_SPEED);
}

void Chassis::stop_movement() {
    _motor_advance->set_analogic_speed(STOP_SPEED);
}

void Chassis::stop_steering() {
    _motor_steering->set_analogic_speed(STOP_SPEED);
}