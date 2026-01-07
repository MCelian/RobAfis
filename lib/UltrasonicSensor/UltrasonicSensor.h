#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include "MeUltrasonicSensor.h"

class UltrasonicSensor {
public:
    UltrasonicSensor(int port);
    int set_detection_threshold(int thresholdCm);
    int get_distance();
    boolean is_object_detected();
private:
    MeUltrasonicSensor* _sensor;
    int _detection_threshold_cm;
    int _last_valid;
};

#endif