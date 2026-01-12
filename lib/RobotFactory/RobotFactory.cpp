#include "RobotFactory.h"

Robot* RobotFactory::createRugbyRobot() {
    RobotBuilder builder;
    RobotDirector director(&builder);

    director.buildFullRugbyRobot();

    return builder.getResult();
}
