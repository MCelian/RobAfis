#include "Robot.h"
#include "MeUltrasonicSensor.h"
#include "Ihm.h"

// Global IHM instance is defined in main.cpp
extern Ihm ihm;

Robot::Robot() {
    _chassis = nullptr;
    _arm = nullptr;
    _claw = nullptr;
    _ultrasonicSensor = nullptr;
    _lineFollowerSensor = nullptr;
    _colorSensor = nullptr;
}

Robot::~Robot() {
    delete _arm;
    delete _chassis;
    delete _arm;
    delete _claw;
    delete _ultrasonicSensor;
    delete _lineFollowerSensor;
    delete _colorSensor;
}

void Robot::doEmergencyStop() {
    _chassis->advanceStop();
    _arm->stop();
    _claw->stop();
}

void Robot::doScenarioAutoTest() {
    while (!_ultrasonicSensor->isObjectDetected()) { _chassis->advanceForward(); }
    _chassis->advanceStop();
    _claw->stop();
    _claw->open();
    delay(3000);
    _claw->stop();
    _arm->moveToGrabPosition();
    _claw->close();
    delay(6000);
    _claw->stop();
    _arm->stop();
    _arm->lower();
    delay(3000);
    _arm->stop();
    while (_colorSensor->getColor() != _colorSensor->GREEN) {
        Serial.println(_colorSensor->getColor());
        _chassis->advanceForward();
    }
    _arm->moveToGrabPosition();
    
    ihm.writeCommand("POINT5 5");
}

void Robot::pivotLookLeft() {
    // To point NOSE Left, we must steer RIGHT and reverse
    _chassis->steerRight();
    _chassis->advanceBackward();
    _chassis->waitAndKeepAlive(600); // Adjust this time to turn ~30-45 degrees
    _chassis->advanceStop();
    _chassis->waitAndKeepAlive(200); // Let vibrations settle
}

void Robot::pivotLookRight() {
    // To point NOSE Right, we must steer LEFT and reverse
    _chassis->steerLeft();
    _chassis->advanceBackward();
    _chassis->waitAndKeepAlive(600); 
    _chassis->advanceStop();
    _chassis->waitAndKeepAlive(200);
}

void Robot::doScenarioTry() {
    Serial.println("doScenarioTry: START");
    // ---------------------------------------------------------
    // PHASE 1: THE SCAN (Doing "Niches")
    // ---------------------------------------------------------
    Serial.println("PHASE 1: SCAN - measuring center");
    
    // 1. Measure CENTER
    _chassis->steerCenter();
    _chassis->waitAndKeepAlive(200);
    _distCenter = _ultrasonicSensor->getDistance();
    Serial.print("Measured CENTER distance: ");
    Serial.println(_distCenter);

    // while (true) {
    //     _distCenter = _ultrasonicSensor->getDistance();
    //     Serial.print("Measured CENTER distance: ");
    //     Serial.println(_distCenter);
    // }

    // 2. Measure LEFT
    Serial.println("Measuring LEFT (pivot look left)");
    // We reverse-turn to point the nose left
    pivotLookLeft(); 
    _distLeft = _ultrasonicSensor->getDistance();
    Serial.print("Measured LEFT distance: ");
    Serial.println(_distLeft);

    // 3. Measure RIGHT
    Serial.println("Measuring RIGHT (swing from left to right)");
    // We are currently pointing Left. We need to swing all the way Right.
    // So we do the "Pivot Right" move TWICE (or for double time)
    _chassis->steerLeft(); // Steer Left + Reverse = Nose goes Right
    _chassis->advanceBackward();
    _chassis->waitAndKeepAlive(1200); // Double time to swing from Left to Right
    _chassis->advanceStop();
    _chassis->waitAndKeepAlive(200);
    _distRight = _ultrasonicSensor->getDistance();
    Serial.print("Measured RIGHT distance: ");
    Serial.println(_distRight);

    // 4. Re-Center (Roughly)
    Serial.println("Re-centering after scan");
    // We are pointing Right. Pivot halfway back to center.
    _chassis->steerRight();
    _chassis->advanceBackward();
    _chassis->waitAndKeepAlive(600);
    _chassis->advanceStop();

    // ---------------------------------------------------------
    // PHASE 2: THE DECISION
    // ---------------------------------------------------------
    Serial.println("PHASE 2: DECISION - evaluating best direction");

    // Default to going straight
    int bestDir = 0; // 0=Center, -1=Left, 1=Right
    int maxDist = _distCenter;
    Serial.print("Initial best = CENTER (dist=");
    Serial.print(maxDist);
    Serial.println(")");

    // Is Left better?
    if (_distLeft > maxDist) {
        maxDist = _distLeft;
        bestDir = -1;
        Serial.print("LEFT is better (dist=");
        Serial.print(_distLeft);
        Serial.println(")");
    }
    // Is Right even better?
    if (_distRight > maxDist) {
        maxDist = _distRight;
        bestDir = 1;
        Serial.print("RIGHT is best (dist=");
        Serial.print(_distRight);
        Serial.println(")");
    }

    Serial.print("Decision: bestDir=");
    Serial.print(bestDir);
    Serial.print(" maxDist=");
    Serial.println(maxDist);

    // ---------------------------------------------------------
    // PHASE 3: EXECUTION (Go to Green Zone)
    // ---------------------------------------------------------
    Serial.println("PHASE 3: EXECUTION");

    if (bestDir == -1) {
        Serial.println("Action: TURN LEFT and drive into gap");
        // TURN LEFT and Drive
        _chassis->steerLeft();
        _chassis->advanceForward();
        _chassis->waitAndKeepAlive(1000); // Turn into the gap
    } 
    else if (bestDir == 1) {
        Serial.println("Action: TURN RIGHT and drive into gap");
        // TURN RIGHT and Drive
        _chassis->steerRight();
        _chassis->advanceForward();
        _chassis->waitAndKeepAlive(1000); // Turn into the gap
    } 
    else {
        Serial.println("Action: CENTER - drive straight");
        // CENTER is best, just start driving
        _chassis->steerCenter();
        _chassis->advanceForward();
    }

    // Now straighten up to drive through the gap to the Green Zone
    Serial.println("Straightening and driving through gap");
    _chassis->steerCenter();
    _chassis->advanceForward();
    
    // Drive for X seconds until we cross the zone
    // If you have a line sensor, replace this timer with `while(!lineDetected)`
    _chassis->waitAndKeepAlive(3000); 

    // Stop safely
    Serial.println("Stopping chassis");
    _chassis->advanceStop();

    Serial.println("doScenarioTry: END");
}

void Robot::doScenarioConversion() {

}

void Robot::getRobotData() {
    // Get Color data from the color sensor
    int color = _colorSensor->getColor();
    String colorName = _colorSensor->getCurrentColorName();
    
    // Get Distance data from the ultrasonic sensor
    int distance = _ultrasonicSensor->getDistance();
    
    // Get Line Sensor data from the line follower sensor
    int lineSensorState = _lineFollowerSensor->readSensors();
    bool isLineDetected = _lineFollowerSensor->isLineDetected();
    
    // Print the data to Serial for debugging
    Serial.print("Couleur détectée: ");
    Serial.print(colorName);
    Serial.print(" (");
    Serial.print(color);
    Serial.println(")");
    
    Serial.print("Distance mesurée (cm): ");
    Serial.println(distance);
    
    Serial.print("État capteur de ligne: ");
    Serial.println(lineSensorState);
    
    Serial.print("Ligne détectée: ");
    Serial.println(isLineDetected ? "OUI" : "NON");
    
    Serial.println("---");
}