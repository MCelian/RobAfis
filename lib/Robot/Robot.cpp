#include "Robot.h"
#include "MeUltrasonicSensor.h"

void Robot::doEmergencyStop() {
    
}

void Robot::doScenarioAutoTest() {
    Serial.println("doScenarioAutoTest: start");
    while (!_ultrasonicSensor->isObjectDetected()) {
        Serial.println("Foward ");
        Serial.print(_ultrasonicSensor->getDistance());
        _chassis->advanceForward();
        delay(50); // avoid spamming loop/serial
    }
    Serial.println("Object detected: stopping forward");
    _chassis->advanceStop();

    Serial.println("Reversing briefly");
    _chassis->advanceBackward();
    delay(1000);
    _chassis->advanceStop();
    Serial.println("Stopped after backup");

    int distanceLeft = 0;
    int distanceRight = 0;

    Serial.println("Steering left to measure distance");
    _chassis->steerLeft();
    delay(200); // allow steering to settle
    distanceLeft = _ultrasonicSensor->getDistance();
    Serial.print("Distance left: ");
    Serial.println(distanceLeft);

    Serial.println("Steering right to measure distance");
    _chassis->steerRight();
    delay(200);
    distanceRight = _ultrasonicSensor->getDistance();
    Serial.print("Distance right: ");
    Serial.println(distanceRight);

    if (distanceLeft <= distanceRight) {
        Serial.println("Decision: steer right");
        _chassis->steerRight();
    } else {
        Serial.println("Decision: steer left");
        _chassis->steerLeft();
    }

    Serial.println("Backing up after steering");
    _chassis->advanceBackward();
    delay(2000);
    _chassis->advanceStop();

    _chassis->steerCenter();
    Serial.println("doScenarioAutoTest: end");
}

void Robot::doScenarioTry() {
    Serial.println("doScenarioTry: start");
    Serial.println(_lineFollowerSensor->readSensors());
}

void Robot::doScenarioConversion() {

}
