#ifndef ROBOT_H
#define ROBOT_H

#include "Arduino.h"
#include "Chassis.h"
#include "Arm.h"
#include "Motor.h"
#include "UltrasonicSensor.h"
#include "Gyroscope.h"
#include "LineFollowerSensor.h"

#define LINE_FOLLOWER_SENSOR_PORT PORT_8
#define COLOR_SENSOR_PORT PORT_7
#define ULTRASOUND_SENSOR_PORT PORT_6
#define GYRO_SENSOR_PORT PORT_5

#define CHASSIS_FB_MOTOR_PORT PORT1B
#define CHASSIS_LR_MOTOR_PORT PORT2B
#define ARM_MOTOR_PORT PORT3B
#define ARM_MOTOR_CLAW_PORT PORT4B

class Robot {
public:
    Robot();
    ~Robot();

    Chassis* chassis();
    Arm* arm();
    void move_arm();
    void move();
    void initialize_sensors();
    void initialize_motors_position();
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