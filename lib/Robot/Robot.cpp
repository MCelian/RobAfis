#include "Robot.h"

UltrasonicSensor* Robot::_staticUltrasoundSensor = nullptr;
LineFollowerSensor* Robot::_staticLineFollowerSensor = nullptr;

bool Robot::checkObstacle() {
    if (_staticUltrasoundSensor != nullptr) {
        return _staticUltrasoundSensor->isObjectDetected();
    }
    return false;
}

bool Robot::checkLineDetection() {
    if (_staticLineFollowerSensor != nullptr) {
        return _staticLineFollowerSensor->isLineDetected();
    }
    return false;
}

Robot::~Robot() {
    delete _chassis;
    delete _arm;
    delete _claw;
    delete _ultrasonicSensor;
    delete _lineFollowerSensor;
    delete _colorSensor;
}

void Robot::initialize() {
    initializeComponent(_ultrasonicSensor);
    initializeComponent(_lineFollowerSensor);
    initializeComponent(_colorSensor);
    initializeComponent(_claw);
    initializeComponent(_arm);
    initializeComponent(_chassis);
}

// Claw methods
void Robot::closeClawDuringMs(int durationMs) {
    _claw->closeDuringMs(durationMs);
}

void Robot::openClawDuringMs(int durationMs) {
    _claw->openDuringMs(durationMs);
}

// Arm methods
void Robot::moveArmToGrabPosition() {
    _arm->moveToGrabPosition();
}

void Robot::moveArmToNeutralPosition() {
    // TODO
}

// Chassis methods
void Robot::advanceForwardDuringMs(int duration) {
    _chassis->advanceForwardDuringMs(duration);
}

void Robot::advanceBackwardDuringMs(int duration) {
    _chassis->advanceBackwardDuringMs(duration);

}

void Robot::advanceForwardUntilObstacle() {
    _chassis->advanceForwardDuringMs(60000, checkObstacle);
}

void Robot::advanceForwardUntilLine() {
    _chassis->advanceForwardDuringMs(60000, checkLineDetection);
}

void Robot::steerCenter() {
    _chassis->steerToCenter();
}

void Robot::pivotLookLeft() {
    _chassis->pivotLookLeft();
}

void Robot::pivotLookRight() {
    _chassis->pivotLookRight();
}

// Concrete actions
void Robot::stopAllComponents() {
    _chassis->advanceStop();
    _arm->stop();
    _claw->stop();
}

bool Robot::advanceForwardUntilPointZone() {
    unsigned long startTime = millis();
    int timeoutMs = 10000;
    const int stepMs = 100;
    while (_colorSensor->getColor() != _colorSensor->GREEN && (millis() - startTime) < (unsigned long)timeoutMs) {
        Serial.println(_colorSensor->getColor());
        _chassis->advanceForwardDuringMs(stepMs);
    }
    if (getCurrentZone() == "En but") {
        _arm->moveToGrabPosition();
        return true;
    }
    return false;
}

void Robot::searchAndGrabBall() {
    if (!_isBallInClaw) return;
    advanceForwardUntilObstacle();
    openClawDuringMs(3000);
    moveArmToGrabPosition();
    closeClawDuringMs(6000);
}

void Robot::goTo22Zone() {
    if (getCurrentZone() != "Centrale ou zone 22") return;
    advanceForwardUntilObstacle();
}