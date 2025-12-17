#ifndef ARM_H
#define ARM_H

#include "Motor.h"

class Arm {
public:
    Arm(int motor_arm_port, int motor_claw_port);
    void raise();
    void lower();
    void open_claw();
    void close_claw();
    void stop_claw();
    void stop();

private:
    friend class Robot; // Allow Robot class to access private members
    Motor* _motor_arm;
    Motor* _motor_claw;
};

#endif