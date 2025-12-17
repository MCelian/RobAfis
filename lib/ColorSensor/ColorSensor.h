#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include "MeColorSensor.h"

#define WHITE 0
#define PINK 1
#define RED 2
#define ORANGE 3
#define YELLOW 4
#define GREEN 5
#define CYAN 6
#define BLUE 7
#define PURPLE 8
#define BLACK 9
#define GOLD 10

#define ZONE_START_COLOR BLUE
#define ZONE_CENTER_COLOR WHITE
#define ZONE_TWENTY_TWO_COLOR WHITE
#define ZONE_POINT_COLOR GREEN
#define ZONE_BAR_COLOR RED

class ColorSensor;

class ColorSensor {
public:
    ColorSensor(MeColorSensor* s);
    void initialize();
    int get_color();
    int get_red();
    int get_green();
    int get_blue();
    boolean is_in_start_zone();
    boolean is_in_center_or_twenty_two_zone();
    boolean is_in_point_zone();
    boolean is_in_bar_zone();

private:
    MeColorSensor* _s;
};

#endif