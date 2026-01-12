#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int port) {
    _sensor = new MeUltrasonicSensor(port);
    _detectionThresholdCm = 19;
    _lastValid = 0;
}

int UltrasonicSensor::setDetectionThreshold(int thresholdCm) {
    _detectionThresholdCm = thresholdCm;
    return true;
}

int UltrasonicSensor::getDistance() {
    int sum = 0;
    int attempts = 0;
    for (int attempt = 0; attempt < 5; attempt++) {
        int dist = _sensor->distanceCm();
        if (dist > 0 && dist < 400) {
            _lastValid = dist;
            sum += dist;
            attempts++;
        }
    }
    if (attempts > 0) {
        _lastValid = (sum + 2) / (attempts);
    }
    return _lastValid;
}

bool UltrasonicSensor::isObjectDetected() {
    return getDistance() < _detectionThresholdCm;
}
