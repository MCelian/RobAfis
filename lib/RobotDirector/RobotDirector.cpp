#include "RobotDirector.h"

RobotDirector::RobotDirector(RobotBuilder* builder) : _builder(builder) {}

RobotDirector::~RobotDirector() {}

void RobotDirector::buildFullRugbyRobot() {
    _builder->reset();
    _builder->addChassis();
    _builder->addArm();
    _builder->addClaw();
    _builder->addUltrasonicSensor(6);
    _builder->addLineFollowerSensor(7);
    _builder->addColorSensor(8);
}

void RobotDirector::createChassisRobot() {
    _builder->reset();
    _builder->addChassis();
}