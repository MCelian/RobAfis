#include "RobotBuilder.h"

RobotBuilder::RobotBuilder() {
    _robot = nullptr;
    reset();
}

RobotBuilder::~RobotBuilder() {
    if (_robot != nullptr) {
        delete _robot;
    }
}

void RobotBuilder::reset() {
    if (_robot != nullptr) {
        delete _robot;
    }
    _robot = new Robot();
}

Robot* RobotBuilder::getResult() {
    Robot* temp = _robot;
    _robot = nullptr;
    reset();
    return temp;
}

void RobotBuilder::addChassis(int portAdvance, int portSteering) {
    _robot->setChassis(new Chassis(portAdvance, portSteering));
}

void RobotBuilder::addArm(int port) {
    _robot->setArm(new Arm(port));
}

void RobotBuilder::addUltrasonicSensor(int port) {
    _robot->setUltrasonicSensor(new UltrasonicSensor(port));
}