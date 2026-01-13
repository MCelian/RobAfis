#include "RobotBuilder.h"

void isrMotorAdvance();
void isrMotorSteering();
void isrMotorArm();

Motor objMotorAdvance(4, isrMotorAdvance, 56 / 8, 18.0, 0.0, 9.0);
Motor objMotorSteering(2, isrMotorSteering, 72 / 8, 18.0, 0.0, 9.0);
Motor objMotorArm(3, isrMotorArm, 56 / 8, 18.0, 1.5, 9.0);

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
    _robot->setClaw(new Claw(1));
}

void RobotBuilder::addUltrasonicSensor() {
    _robot->setUltrasonicSensor(new UltrasonicSensor(8));
}

void RobotBuilder::addLineFollowerSensor() {
    _robot->setLineFollowerSensor(new LineFollowerSensor(7));
}

void RobotBuilder::addColorSensor() {
    _robot->setColorSensor(new ColorSensor(6));
}