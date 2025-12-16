#ifndef ARM_H
#define ARM_H

#include "Motor.h"

class Arm {
public:
    Arm(Motor* motor, Motor* _motor_claw);
    void raise();
    void lower();
    void open_claw();
    void close_claw();
    void stop_claw();
    void stop();

private:
    friend class Robot; // Allow Robot class to access private members
    Motor* _motor;
    Motor* _motor_claw;
};

#endif