#ifndef CHASSIS_H
#define CHASSIS_H

#include "Gyroscope.h"
#include "Motor.h"

#define STEER_ANGLE_MARGIN 0.5
#define DEFAULT_STEER_SPEED 100

class Chassis {
public:
    Chassis(int motor_advance_port, int motor_steering_port, int gyroscope_port);
    ~Chassis();
    void initialize();
    void forward();
    void backward();
    void reset_direction();
    void stop_movement();
    void stop_steering();
    void update_sensors();
    double get_angle_x();
    double get_angle_y();
    double get_angle_z();
    double angle = 0;
    boolean steer_to_angle(double target_angle);

private:
    friend class Robot;
    Motor* _motor_advance;
    Motor* _motor_steering;
    Gyroscope* _gyroscope;

};

#endif
