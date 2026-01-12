#include "RobotDirector.h"

RobotDirector::RobotDirector(RobotBuilder* builder) : _builder(builder) {}

RobotDirector::~RobotDirector() {}

void RobotDirector::buildFullRugbyRobot(int portUltrasonicSensor, int portLineFollowerSensor, int portColorSensor) {
    _builder->reset();
    _builder->addChassis();
    _builder->addArm();
    _builder->addClaw();
    _builder->addUltrasonicSensor(portUltrasonicSensor);
    _builder->addLineFollowerSensor(portLineFollowerSensor);
    _builder->addColorSensor(portColorSensor);
}

void RobotDirector::createChassisRobot() {
    _builder->reset();
    _builder->addChassis();
}