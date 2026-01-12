#ifndef ROBOT_FACTORY_H
#define ROBOT_FACTORY_H

#include "RobotDirector.h"

class Robot;

class RobotFactory {
public:
    RobotFactory();
    ~RobotFactory();

    static Robot* createRugbyRobot();
    static Robot* createChassisRobot();
};

#endif