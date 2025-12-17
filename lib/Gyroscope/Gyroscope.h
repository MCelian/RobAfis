#ifndef GYROSCOPE_SENSOR_H
#define GYROSCOPE_SENSOR_H

#include "MeGyro.h"

class Gyroscope {
public:
    Gyroscope(int port);
    void initialize();
    void update();
    void calibrate();
    double get_angle_x();
    double get_angle_y();
    double get_angle_z();
    double get_gyro_x();
    double get_gyro_y();

private:
    MeGyro* _s;
    double _initial_x = 0, _initial_y = 0, _initial_z = 0;
};

#endif