#ifndef ROBOT_H
#define ROBOT_H

#include "Chassis.h"
#include "Arm.h"
#include "Claw.h"
#include "UltrasonicSensor.h"
#include "LineFollowerSensor.h"
#include "ColorSensor.h"

class Robot {
public:
    Robot();
    ~Robot();
    void setChassis(Chassis* chassis) {
        delete _chassis;
        _chassis = chassis;
    }

    void setArm(Arm* arm) {
        delete _arm;
        _arm = arm;
    }

    void setClaw(Claw* claw) {
        delete _claw;
        _claw = claw;
    }

    void setUltrasonicSensor(UltrasonicSensor* sensor) {
        if (_ultrasonicSensor != nullptr) {
            delete _ultrasonicSensor;
        }

        _ultrasonicSensor = sensor;

        _staticSensor = sensor;
    }

    void setLineFollowerSensor(LineFollowerSensor* sensor) {
        delete _lineFollowerSensor;
        _lineFollowerSensor = sensor;
    }

    void setColorSensor(ColorSensor* sensor) {
        delete _colorSensor;
        _colorSensor = sensor;
    }

    void advanceForwardUntilObstacle();
    void openClawDuringM(int durationMs);
    void closeClawDuringMs(int durationMs);

    void moveArmToGrabPosition();
    void moveArmToNeutralPosition();

    void advanceFowardUntilPointZone();

    void initializeChassis() {
        _chassis->initialize();
    }

    void initializeArm() {
        _arm->initialize();
    }

    void initializeClaw() {
        _claw->closeUntilLimit();
    }

    void initializeUltrasonicSensor() {
        _ultrasonicSensor->initialize();
    }

    void initializeColorSensor() {
        _colorSensor->initialize();
    }

    void doScenarioAutoTest();
    void doScenarioTry();
    void doScenarioConversion();
    void doEmergencyStop();

    void lineDetectedCountIncrement() {
        _lineDetectedCount++;
    }

    void lineDetectedCountDecrement() {
        _lineDetectedCount--;
    }

    void lineDetectedCountReset() {
        _lineDetectedCount = 0;
    }

    int getColorData() {
        return _colorSensor->getColor();
    }

    int getDistanceData() {
        return _ultrasonicSensor->getDistance();
    }

    int getLineSensorData() {
        return _lineFollowerSensor->readSensors();
    }

    bool isLineDetectedData() {
        return _lineFollowerSensor->isLineDetected();
    }

    String getColorName() {
        _colorSensor->getColor();
        return _colorSensor->getCurrentColorName();
    }

    void getRobotData();
private:
    Chassis* _chassis = nullptr;
    Arm* _arm = nullptr;
    Claw* _claw = nullptr;
    UltrasonicSensor* _ultrasonicSensor = nullptr;
    static UltrasonicSensor* _staticSensor;
    static bool checkObstacle();
    LineFollowerSensor* _lineFollowerSensor = nullptr;
    ColorSensor* _colorSensor = nullptr;
    int _lineDetectedCount = 0;

    void pivotLookLeft();
    void pivotLookRight();
    void realignCenter();
    int _distLeft = 0;
    int _distCenter = 0;
    int _distRight = 0;
};

#endif