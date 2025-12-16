#ifndef ROBOT_H
#define ROBOT_H

#include "Arduino.h"
#include "Chassis.h"
#include "Arm.h"
#include "Motor.h"
#include "UltrasonicSensor.h"
#include "Gyroscope.h"
#include "LineFollowerSensor.h"

class Robot {
public:
    Robot();
    ~Robot();

    Chassis* chassis();
    Arm* arm();
    void move_arm();
    void move();
    void initialize_sensors();
    void do_scenario_auto_test();
    void do_scenario_try();
    void do_scenario_conversion();
    void move_left_right_randomly();
    void do_emergency_stop();

private:
    Arm* _arm;
    Chassis* _chassis;
    UltrasonicSensor* _ultrasonic;
    Gyroscope* _gyroscope;
    LineFollowerSensor* _line_follower_sensor;
};

#endif