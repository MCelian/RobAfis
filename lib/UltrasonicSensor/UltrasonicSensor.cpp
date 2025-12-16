#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(MeUltrasonicSensor* s) : _s(s), _last_valid(0) {}

int UltrasonicSensor::set_detection_threshold(int thresholdCm) {
    _detection_threshold_cm = thresholdCm;
    return true;
}

int UltrasonicSensor::get_distance() {
    int distance = 0;
    int measure = (int)_s->distanceCm();
    if (measure > 5 && measure < 400) {
        distance = measure;
        _last_valid = measure;
    } else {
        distance = _last_valid;
    }

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    return distance;
}

boolean UltrasonicSensor::is_object_detected() {
        Serial.print("Distance: ");
    Serial.print(get_distance());
    Serial.println(" cm");
    return get_distance() < _detection_threshold_cm;
}
