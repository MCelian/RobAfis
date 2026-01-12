#ifndef ROBOT_SENSOR_HELPER_H
#define ROBOT_SENSOR_HELPER_H

// #include "MeLineFollower.h"

// #define S1_IN_S2_IN   (0x00)
// #define S1_IN_S2_OUT  (0x01)
// #define S1_OUT_S2_IN  (0x02)
// #define S1_OUT_S2_OUT (0x03)

class RobotSensorHelper { 
public:
    RobotSensorHelper();

    bool isLineDetected() {
        // return readSensors() != 0;
        return false;
    }

    bool isLineDetectedLeft() {
        // return readSensors() != 1;
        return false;
    }

    bool isLineDetectedRight() {
        // return readSensors() == 2;
        return false;
    }

    bool isLineNotDetected() {
        // return readSensors() == 3;
        return false;
    }
private:
};

#endif