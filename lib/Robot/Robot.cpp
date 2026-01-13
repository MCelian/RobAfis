#include "Robot.h"

UltrasonicSensor* Robot::_staticUltrasoundSensor = nullptr;
LineFollowerSensor* Robot::_staticLineFollowerSensor = nullptr;
ColorSensor* Robot::_staticColorSensor = nullptr;

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

bool Robot::checkColorCode(int code) {
    if (_staticColorSensor != nullptr) {
        int currentCode = _staticColorSensor->getColorCode();
        int delta = abs(currentCode - code);
        Serial.print("current Code: ");
        Serial.println(currentCode);
        Serial.print("Wanted Code: ");
        Serial.println(code);
        Serial.print("Delta: ");
        Serial.println(delta);
        return delta < 500;
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
    //initializeComponent(_arm);
    // initializeComponent(_claw);
    initializeComponent(_chassis);
}

// Claw methods
void Robot::closeClawDuringMs(int durationMs) {
    _claw->closeDuringMs(durationMs);
}

void Robot::openClawDuringMs(int durationMs) {
    _claw->openDuringMs(durationMs);
}

void Robot::openClawUntilLimit() {
    _claw->openUntilLimit();
}

void Robot::closeClawUntilLimit() {
    _claw->closeUntilLimit();
}

// Arm methods
void Robot::moveArmToGrabPosition() {
    _arm->moveToGrabPosition();
}

void Robot::moveArmToNeutralPosition() {
    _arm->moveArmToNeutralPosition();
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
    
    int greenCode = 23595;

    // while (!checkColorCode(greenCode) && (millis() - startTime) < (unsigned long)timeoutMs) {
    while (!checkColorCode(greenCode)) {
        Serial.println("START");
        Serial.println(_colorSensor->getColorCode());
        // _chassis->advanceForwardDuringMs(stepMs);
        return true;
    }
    Serial.println("YESSSSSSSSSSSS");
    return false;
}

void Robot::searchAndGrabBall() {

}

void Robot::goTo22Zone() {
    if (getCurrentZone() != "Centrale ou zone 22") return;
    advanceForwardUntilObstacle();
}