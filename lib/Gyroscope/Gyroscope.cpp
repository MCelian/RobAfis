#include "Gyroscope.h"

Gyroscope::Gyroscope(MeGyro* s) : _s(s) {}

boolean Gyroscope::calibrate() {
    _initial_x = _s->getAngleX();
    _initial_y = _s->getAngleY();
    _initial_z = _s->getAngleZ();
    return true;
}

boolean Gyroscope::initialize() {
    _s->begin();
    calibrate();
    return true;
}

boolean Gyroscope::update() {
    _s->update();
    return true;
}

int Gyroscope::getAngleX() {
    int actual_x = _s->getAngleX();
    return _initial_x - actual_x;
}

int Gyroscope::getAngleY() {
    int actual_y = _s->getAngleY();
    return _initial_y - actual_y;
}

int Gyroscope::getAngleZ() {
    int actual_z = _s->getAngleZ();
    return _initial_z - actual_z;
}