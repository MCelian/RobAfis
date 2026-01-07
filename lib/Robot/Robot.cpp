#include "Robot.h"
Robot::Robot() {
    _chassis = nullptr;
    _arm = nullptr;
}

Robot::~Robot() {
    delete _arm;
    delete _chassis;
}

void Robot::setChassis(Chassis* chassis) {
    delete _chassis;
    _chassis = chassis;
}

void Robot::setArm(Arm* arm) {
    delete _arm;
    _arm = arm;
}

void Robot::setClaw(Claw* claw) {
    delete _claw;
    _claw = claw;
}
void Robot::setUltrasonicSensor(UltrasonicSensor* sensor) {
    delete _ultrasonicSensor;
    _ultrasonicSensor = sensor;
}

void Robot::doEmergencyStop() {
    _chassis->findSteeringLimits();
}


void Robot::doScenarioAutoTest() {

}

void Robot::doScenarioTry() {

}

void Robot::doScenarioConversion() {

}
