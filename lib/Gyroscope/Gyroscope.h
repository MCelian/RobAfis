#ifndef GYROSCOPE_SENSOR_H
#define GYROSCOPE_SENSOR_H

#include "MeGyro.h"

class Gyroscope {
public:
    Gyroscope(MeGyro* s);
    boolean initialize();
    boolean update();
    boolean calibrate();
    int getAngleX();
    int getAngleY();
    int getAngleZ();
private:
    MeGyro* _s;
    int _initial_x = 0, _initial_y = 0, _initial_z = 0;
};

#endif