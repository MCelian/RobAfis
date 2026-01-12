#ifndef ROBOT_DIRECTOR_H
#define ROBOT_DIRECTOR_H

#include "RobotBuilder.h"

class RobotDirector {
public:
    RobotDirector(RobotBuilder* builder);
    ~RobotDirector();

    void buildFullRugbyRobot(int portUltrasonicSensor, int portLineFollowerSensor,  int portColorSensor);
    void createChassisRobot();
private:
    RobotBuilder* _builder;
};

#endif