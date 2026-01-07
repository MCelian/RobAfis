#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int port) {
    _sensor = new MeUltrasonicSensor(port);
    _detection_threshold_cm = 20;
    _last_valid = 0;
}

int UltrasonicSensor::set_detection_threshold(int thresholdCm) {
    _detection_threshold_cm = thresholdCm;
    return true;
}

int UltrasonicSensor::get_distance() {
    return _sensor->distanceCm();
}

boolean UltrasonicSensor::is_object_detected() {
    return get_distance() < _detection_threshold_cm;
}
