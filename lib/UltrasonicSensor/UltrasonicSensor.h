#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include "MeUltrasonicSensor.h"

class UltrasonicSensor {
public:
    UltrasonicSensor(int port) : _detectionThresholdCm(19), _lastValid(0) {
        _sensor = new MeUltrasonicSensor(port);
    };
    
    void initialize() {
        //while (getDistance() == 0 || getDistance() == 400) { getDistance(); }
    }

    int getData() {
        return _sensor->distanceCm();
    }
    
private:
    MeUltrasonicSensor* _sensor;
    int _detectionThresholdCm;
    int _lastValid;
};

#endif