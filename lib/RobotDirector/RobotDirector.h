#ifndef ROBOT_DIRECTOR_H
#define ROBOT_DIRECTOR_H

#include "RobotBuilder.h"

class RobotDirector {
public:
    RobotDirector(RobotBuilder* builder);
    ~RobotDirector();

    void buildFullRugbyRobot(int portAdvance, int portSteering, int portUltrasonic, int portLineFollower);
private:
    RobotBuilder* _builder;
};

#endif