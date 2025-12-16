#ifndef LINE_FOLLOWER_SENSOR_H
#define LINE_FOLLOWER_SENSOR_H

#include "MeLineFollower.h"

class LineFollowerSensor {
public:
    LineFollowerSensor(MeLineFollower* s);
    int read_sensors();
    boolean is_line_detected();
private:
    MeLineFollower* _s;
};

#endif