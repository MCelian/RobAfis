#include "ColorSensor.h"

ColorSensor::ColorSensor(MeColorSensor* s) : _s(s) {}

void ColorSensor::initialize() {
    _s->ColorIdentify();
}

int ColorSensor::get_color() {
    return _s->ColorIdentify();
}

int ColorSensor::get_red() {
    return _s->ReturnRedData();
}

int ColorSensor::get_green() {
    return _s->ReturnGreenData();
}

int ColorSensor::get_blue() {
    return _s->ReturnBlueData();
}

boolean ColorSensor::is_in_start_zone() {
    return get_color() == ZONE_START_COLOR;
}

boolean ColorSensor::is_in_center_or_twenty_two_zone() {
    int color = get_color();
    return color == ZONE_CENTER_COLOR || color == ZONE_TWENTY_TWO_COLOR;
}

boolean ColorSensor::is_in_point_zone() {
    return get_color() == ZONE_POINT_COLOR;
}

boolean ColorSensor::is_in_bar_zone() {
    return get_color() == ZONE_BAR_COLOR;
}
