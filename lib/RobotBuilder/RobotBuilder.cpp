#include "RobotBuilder.h"

void isrMotorAdvance();
void isrMotorSteering();
void isrMotorArm();

Motor objMotorAdvance(1, isrMotorAdvance, 56 / 8, 40.0, 1.5, 12.0);
Motor objMotorSteering(2, isrMotorSteering, 72 / 8, 18.0, 0.0, 9.0) ;
Motor objMotorArm(3, isrMotorArm, 56 / 8, 40.0, 1.5, 12.0);

void isrMotorAdvance() { objMotorAdvance.handleInterrupt(); }
void isrMotorSteering() { objMotorSteering.handleInterrupt(); }
void isrMotorArm() { objMotorArm.handleInterrupt(); }

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


void RobotBuilder::addChassis() {
    _robot->setChassis(new Chassis(&objMotorAdvance, &objMotorSteering));
}

void RobotBuilder::addArm() {
    _robot->setArm(new Arm(&objMotorArm));
}

void RobotBuilder::addClaw() {
    _robot->setClaw(new Claw(12));
}

void RobotBuilder::addUltrasonicSensor(int port) {
    _robot->setUltrasonicSensor(new UltrasonicSensor(port));
}

void RobotBuilder::addLineFollowerSensor(int port) {
    _robot->setLineFollowerSensor(new LineFollowerSensor(port));
}

void RobotBuilder::addColorSensor(int port) {
    _robot->setColorSensor(new ColorSensor(port));
}