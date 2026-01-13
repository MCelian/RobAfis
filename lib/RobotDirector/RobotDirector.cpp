#include "RobotDirector.h"

RobotDirector::RobotDirector(RobotBuilder* builder) : _builder(builder) {}

RobotDirector::~RobotDirector() {}

void RobotDirector::buildFullRugbyRobot() {
    _builder->reset();
    _builder->addChassis();
    _builder->addArm();
    _builder->addClaw();
    _builder->addUltrasonicSensor();
    _builder->addLineFollowerSensor();
    _builder->addColorSensor();
}

void RobotDirector::createChassisRobot() {
    _builder->reset();
    _builder->addChassis();
}