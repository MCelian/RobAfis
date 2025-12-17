#include "Gyroscope.h"
#include "MeGyro.h"

Gyroscope::Gyroscope(int port) {
    _s = new MeGyro(port);
}

void Gyroscope::initialize() {
    _s->begin();
    delay(100);
    calibrate();
}

void Gyroscope::update() {
    _s->fast_update();
}

void Gyroscope::calibrate() {
    const int samples = 20;
    double sumx = 0, sumy = 0, sumz = 0;
    for (int i = 0; i < samples; ++i) {
        _s->fast_update();
        sumx += _s->getAngleX();
        sumy += _s->getAngleY();
        sumz += _s->getAngleZ();
        delay(10);
    }
    _initial_x = sumx / samples;
    _initial_y = sumy / samples;
    _initial_z = sumz / samples;
}

double Gyroscope::get_angle_x() {
    return _s->getAngleX() - _initial_x;
}

double Gyroscope::get_angle_y() {
    return _s->getAngleY() - _initial_y;
}

double Gyroscope::get_angle_z() {
    return _s->getAngleZ() - _initial_z;
}

double Gyroscope::get_gyro_x() {
    update();
    return _s->getGyroX();
}

double Gyroscope::get_gyro_y() {
    update();
    return _s->getGyroY();
}