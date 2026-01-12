#ifndef LINE_FOLLOWER_SENSOR_H
#define LINE_FOLLOWER_SENSOR_H

#include "MeLineFollower.h"

#define S1_IN_S2_IN   (0x00)
#define S1_IN_S2_OUT  (0x01)
#define S1_OUT_S2_IN  (0x02)
#define S1_OUT_S2_OUT (0x03)

class LineFollowerSensor {
public:
    LineFollowerSensor(int port) {
        _sensor = new MeLineFollower(port);
    }

        bool isLineDetected() {
        return readSensors() != 0;
    }

    bool isLineDetectedLeft() {
        return readSensors() != 1;
    }

    bool isLineDetectedRight() {
        return readSensors() == 2;
    }

    bool isLineNotDetected() {
        return readSensors() == 3;
    }

    void lineDetectedCountIncrement() {
        _lineDetectedCount++;
    }

    void lineDetectedCountDecrement() {
        _lineDetectedCount--;
    }

    void lineDetectedCountReset() {
        _lineDetectedCount = 0;
    }

    int getLineDetectedCount() {
        return _lineDetectedCount;
    }
private:
    MeLineFollower* _sensor;
    int _lineDetectedCount = 0;

    int readSensors() {
        return _sensor->readSensors();
    }
};

#endif