#include "ColorSensor.h"
#include "Arduino.h"

ColorSensor::ColorSensor(MeColorSensor* s) : _s(s) {}

void ColorSensor::init() {
    _s->ColorIdentify();
    _s->TurnOnLight();
}

int ColorSensor::getColor() {
    return _s->ColorIdentify();
}