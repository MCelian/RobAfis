#include "LineFollowerSensor.h"

LineFollowerSensor::LineFollowerSensor(int port) {
    _sensor = new MeLineFollower(port);
}

int LineFollowerSensor::readSensors() {
    return _sensor->readSensors();
}

bool LineFollowerSensor::isLineDetected() {
    return readSensors() != 0;
}

bool LineFollowerSensor::isLineDetectedLeft() {
    return readSensors() != 1;
}

bool LineFollowerSensor::isLineDetectedRight() {
    return readSensors() == 2;
}

bool LineFollowerSensor::isLineNotDetected() {
    return readSensors() == 3;
}