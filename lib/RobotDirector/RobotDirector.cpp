#include "RobotDirector.h"

RobotDirector::RobotDirector(RobotBuilder* builder) : _builder(builder) {}

RobotDirector::~RobotDirector() {}

void RobotDirector::buildFullRugbyRobot(int portAdvance, int portSteering, int portArm, int portClaw, int portUltrasonicSensor, int portLineFollowerSensor, int portColorSensor) {
    _builder->reset();
    _builder->addChassis(portAdvance, portSteering);
    _builder->addArm(portArm);
    _builder->addClaw(portClaw);
    _builder->addUltrasonicSensor(portUltrasonicSensor);
    _builder->addLineFollowerSensor(portLineFollowerSensor);
    _builder->addColorSensor(portColorSensor);
}