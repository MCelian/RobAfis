#include "LineFollowerSensor.h"

LineFollowerSensor::LineFollowerSensor(MeLineFollower* s) : _s(s) {}

int LineFollowerSensor::readSensors() {
    return _s->readSensors();
}

bool LineFollowerSensor::isLineDetected() {
    return readSensors() != 3;
}