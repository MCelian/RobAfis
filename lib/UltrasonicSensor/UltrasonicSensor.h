#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include "MeUltrasonicSensor.h"

class UltrasonicSensor {
public:
    UltrasonicSensor(int port) {
        _sensor = new MeUltrasonicSensor(port);
    };
    
    void initialize() {
        getDistance();
    }

    int getDistance() {
        int distance = _sensor->distanceCm();
        _lastValid = distance < 400 && distance > 0 ? distance : _lastValid;
        return _lastValid;
    }

    bool isObjectDetected() {
        int distance = getDistance();
        return distance > 0 && distance < _detectionThresholdCm;
    }
private:
    MeUltrasonicSensor* _sensor;
    int _detectionThresholdCm = 19;
    int _lastValid = 400;
};

#endif