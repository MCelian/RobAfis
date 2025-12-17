#include "Arm.h"
#include "Motor.h"

#define MAX_SPEED 255

Arm::Arm(int motor_arm_port, int motor_claw_port)
{
    _motor_arm = new Motor(motor_arm_port);
    _motor_claw = new Motor(motor_claw_port);
}

void Arm::raise() {
    _motor_arm->set_analogic_speed(MAX_SPEED);
}

void Arm::lower() {
    _motor_arm->set_analogic_speed(-MAX_SPEED);
}

void Arm::stop() {
    _motor_arm->set_analogic_speed(0);
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
