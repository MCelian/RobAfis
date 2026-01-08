#include "RobotDirector.h"

RobotDirector::RobotDirector(RobotBuilder* builder) : _builder(builder) {}

RobotDirector::~RobotDirector() {}

void RobotDirector::buildFullRugbyRobot(int portAdvance, int portSteering, int portUltrasonic, int portLineFollower) {
    _builder->reset();
    _builder->addChassis(portAdvance, portSteering);
    _builder->addUltrasonicSensor(portUltrasonic);
    _builder->addLineFollowerSensor(portLineFollower);
}