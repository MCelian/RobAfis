#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int port) {
    _sensor = new MeUltrasonicSensor(port);
    _detectionThresholdCm = 20;
    _lastValid = 0;
}

int UltrasonicSensor::setDetectionThreshold(int thresholdCm) {
    _detectionThresholdCm = thresholdCm;
    return true;
}

int UltrasonicSensor::getDistance() {
    return _sensor->distanceCm();
}

boolean UltrasonicSensor::isObjectDetected() {
    return getDistance() < _detectionThresholdCm;
}
