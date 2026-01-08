#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include "Wire.h"
#include "MeColorSensor.h"

class ColorSensor {
public:
    ColorSensor(int port) { _sensor = new MeColorSensor(port); };
    void initialize() { _sensor->TurnOnmodule(); _sensor->SensorInit(); }
    int getColor() { return _sensor->ColorIdentify(); }
    int WHITE  = 0;
    int PINKE  = 1;
    int RED    = 2;
    int ORANGE = 3;
    int YELLOW = 4;
    int GREEN  = 5;
    int CYAN   = 6;
    int BLUE   = 7;
    int PURPLE = 8;
    int BLACK  = 9;
    int GOLD   = 10;
private:
    MeColorSensor* _sensor;
};

#endif