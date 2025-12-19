#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(MeUltrasonicSensor* s) : _s(s), _last_valid(0) {}

int UltrasonicSensor::set_detection_threshold(int thresholdCm) {
    _detection_threshold_cm = thresholdCm;
    return true;
}

int UltrasonicSensor::get_distance() {
    return _s->distanceCm();
}

boolean UltrasonicSensor::is_object_detected() {
    return get_distance() < _detection_threshold_cm;
}
