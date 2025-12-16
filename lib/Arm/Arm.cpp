#include "Arm.h"
#include "Motor.h"

#define MAX_SPEED 255

Arm::Arm(Motor* motor, Motor* motor_claw)
{
    _motor = motor;
    _motor_claw = motor_claw;
}

void Arm::raise() {
    _motor->set_analogic_speed(MAX_SPEED);
}

void Arm::lower() {
    _motor->set_analogic_speed(-MAX_SPEED);
}

void Arm::stop() {
    _motor->set_analogic_speed(0);
}

void Arm::close_claw() {
    _motor_claw->set_analogic_speed(MAX_SPEED);
}

void Arm::open_claw() {
    _motor_claw->set_analogic_speed(-MAX_SPEED);
}

void Arm::stop_claw() {
    _motor_claw->set_analogic_speed(0);
}
