#ifndef ROBOT_H
#define ROBOT_H

#include "Arduino.h"
#include "Chassis.h"
#include "Arm.h"
#include "Motor.h"
#include "UltrasonicSensor.h"
#include "LineFollowerSensor.h"
#include "ColorSensor.h"

#define LINE_FOLLOWER_SENSOR_PORT PORT_8
#define COLOR_SENSOR_PORT PORT_7
#define GYRO_SENSOR_PORT PORT_6
#define ULTRASOUND_SENSOR_PORT PORT_5

#define CHASSIS_ADVANCE_MOTOR_PORT PORT1B
#define CHASSIS_STEERING_MOTOR_PORT PORT2B
#define ARM_MOTOR_PORT PORT3B
#define ARM_MOTOR_CLAW_PORT PORT4B

#define ZONE_START_CODE 0
#define ZONE_CENTER_CODE 1
#define ZONE_TWENTY_TWO_CODE 2
#define ZONE_POINT_CODE 3
#define ZONE_BAR_CODE 4

class Robot {
public:
    Robot();
    ~Robot();

    Chassis* chassis();
    Arm* arm();
    void initialize_sensors();
    void do_emergency_stop();
    void do_mechanic_stop();
    void do_electric_stop();
    void do_pause();
    void do_resume();
    void do_scenario_auto_test();
    void do_scenario_try();
    void do_scenario_conversion();
    
    String get_robot_data();
    int get_score();
    int update_current_zone();
    int get_current_zone();
    
private:
    Arm* _arm;
    Chassis* _chassis;
    UltrasonicSensor* _ultrasonic;
    LineFollowerSensor* _line_follower_sensor;
    ColorSensor* _color_sensor;

    int _current_zone = 0;
    int _previous_zone = 0;
    int _score = 0;
    boolean _is_paused = false;
    String _status = "Initialized";
};

#endif