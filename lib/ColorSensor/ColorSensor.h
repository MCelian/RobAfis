#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include "Wire.h"
#include "MeColorSensor.h"

class ColorSensor {
public:
    static int const WHITE  = 0;
    static int const PINKE  = 1;
    static int const RED    = 2;
    static int const ORANGE = 3;
    static int const YELLOW = 4;
    static int const GREEN  = 5;
    static int const CYAN   = 6;
    static int const BLUE   = 7;
    static int const PURPLE = 8;
    static int const BLACK  = 9;
    static int const GOLD   = 10;

    ColorSensor(int port) {
        _sensor = new MeColorSensor(port);
    }

    void initialize() {
        _sensor->TurnOnmodule();
        _sensor->SensorInit();
    }

    int getColor() {
        return _sensor->ColorIdentify();
    }

    String getColorName(int colorValue) {
        switch(colorValue) {
            case WHITE:  return "BLANC";
            case PINKE:  return "ROSE";
            case RED:    return "ROUGE";
            case ORANGE: return "ORANGE";
            case YELLOW: return "JAUNE";
            case GREEN:  return "VERT";
            case CYAN:   return "CYAN";
            case BLUE:   return "BLEU";
            case PURPLE: return "VIOLET";
            case BLACK:  return "NOIR";
            case GOLD:   return "OR";
            default: return "INCONNU";
        }
    }
    
    String getCurrentColorName() {
        getColor();
        return getColorName(getColor());
    }
private:
    MeColorSensor* _sensor;
};

#endif