#include "LineFollowerSensor.h"

LineFollowerSensor::LineFollowerSensor(MeLineFollower* s) : _s(s) {}

int LineFollowerSensor::read_sensors() {
    return _s->readSensors();
}

boolean LineFollowerSensor::is_line_detected() {
    return read_sensors() != 3;
}