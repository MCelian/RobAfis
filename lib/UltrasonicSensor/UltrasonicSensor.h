#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include "MeUltrasonicSensor.h"

class UltrasonicSensor {
public:
    UltrasonicSensor(int port);
    void initialize() { while (getDistance() == 0 || getDistance() == 400) { getDistance(); } };
    int setDetectionThreshold(int thresholdCm);
    int getDistance();
    boolean isObjectDetected();
private:
    MeUltrasonicSensor* _sensor;
    int _detectionThresholdCm;
    int _lastValid;
};

#endif