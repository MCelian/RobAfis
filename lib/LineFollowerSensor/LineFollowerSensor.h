#ifndef LINE_FOLLOWER_SENSOR_H
#define LINE_FOLLOWER_SENSOR_H

#include "MeLineFollower.h"

#define S1_IN_S2_IN   (0x00)
#define S1_IN_S2_OUT  (0x01)
#define S1_OUT_S2_IN  (0x02)
#define S1_OUT_S2_OUT (0x03)

class LineFollowerSensor {
public:
    LineFollowerSensor(int port);
    int readSensors();
    bool isLineDetected();
    bool isLineDetectedLeft();
    bool isLineDetectedRight();
    bool isLineNotDetected();
private:
    MeLineFollower* _sensor;
};

#endif