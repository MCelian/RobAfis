#ifndef LINE_FOLLOWER_SENSOR_H
#define LINE_FOLLOWER_SENSOR_H

#include "MeLineFollower.h"

class LineFollowerSensor {
public:
    LineFollowerSensor(MeLineFollower* s);
    int readSensors();
    bool isLineDetected();
private:
    MeLineFollower* _s;
};

#endif