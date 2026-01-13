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
    void addUltrasonicSensor();
    void addLineFollowerSensor();
    void addColorSensor();
private:
    Robot* _robot;
};

#endif