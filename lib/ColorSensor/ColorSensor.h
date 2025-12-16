#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include "MeColorSensor.h"

class ColorSensor;

class ColorSensor {
public:
    ColorSensor(MeColorSensor* s);
    void init();
    int getColor();
private:
    MeColorSensor* _s;
};

#endif