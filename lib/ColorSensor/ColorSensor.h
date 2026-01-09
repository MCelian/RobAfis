#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include "Wire.h"
#include "MeColorSensor.h"

class ColorSensor {
public:
    ColorSensor(int port) { _sensor = new MeColorSensor(port); };
    void initialize() { _sensor->TurnOnmodule(); _sensor->SensorInit(); }
    int getColor() { return _sensor->ColorIdentify(); }
    String getColorName(int colorValue) {
        switch(colorValue) {
            case 0:  return "BLANC";
            case 1:  return "ROSE";
            case 2:  return "ROUGE";
            case 3:  return "ORANGE";
            case 4:  return "JAUNE";
            case 5:  return "VERT";
            case 6:  return "CYAN";
            case 7:  return "BLEU";
            case 8:  return "VIOLET";
            case 9:  return "NOIR";
            case 10: return "OR";
            default: return "INCONNU";
        }
    }
    String getCurrentColorName() {
        return getColorName(getColor());
    }
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