#ifndef ROBOT_BUILDER_H
#define ROBOT_BUILDER_H

#include "Robot.h"
#include "Motor.h"
#include "UltrasonicSensor.h"

class RobotBuilder {
public:
    RobotBuilder();
    ~RobotBuilder();

    void reset();
    Robot* getResult();

    void addChassis();
    void addArm();
    void addClaw();
    void addUltrasonicSensor(int port);
    void addLineFollowerSensor(int port);
    void addColorSensor(int port);
private:
    Robot* _robot;
};

#endif