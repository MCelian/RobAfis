#include "RobotFactory.h"

#define PORT_ULTRASONIC_SENSOR 6
#define PORT_LINE_FOLLOWER_SENSOR 7
#define PORT_COLOR_SENSOR 8

Robot* RobotFactory::createRugbyRobot() {
    RobotBuilder builder;
    RobotDirector director(&builder);

    director.buildFullRugbyRobot(
        PORT_ULTRASONIC_SENSOR,
        PORT_LINE_FOLLOWER_SENSOR,
        PORT_COLOR_SENSOR
    );

    return builder.getResult();
}
