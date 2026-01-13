#ifndef ROBOT_H
#define ROBOT_H

#include "Chassis.h"
#include "Arm.h"
#include "Claw.h"
#include "UltrasonicSensor.h"
#include "LineFollowerSensor.h"
#include "ColorSensor.h"

template <typename RobotComponent>
void initializeComponent(RobotComponent* robotComponent) {
    robotComponent->initialize();
}

class Robot {
public:
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
        _staticUltrasoundSensor = sensor;
    }

    void setLineFollowerSensor(LineFollowerSensor* sensor) {
        if (_lineFollowerSensor != nullptr) {
            delete _lineFollowerSensor;
        }

        _lineFollowerSensor = sensor;
        _staticLineFollowerSensor = sensor;
    }

    void setColorSensor(ColorSensor* sensor) {
        if (_colorSensor != nullptr) {
            delete _colorSensor;
        }

        _colorSensor = sensor;
        _staticColorSensor = sensor;
    }

    void initialize();

    // Claw methods
    void openClawDuringMs(int durationMs);
    void closeClawDuringMs(int durationMs);
    void openClawUntilLimit();
    void closeClawUntilLimit();

    // Arm methods
    void moveArmToGrabPosition();

    void moveArmToNeutralPosition();

    // Chassis methods
    void advanceForwardDuringMs(int duration);
    void advanceBackwardDuringMs(int duration);
    void advanceForwardUntilObstacle();
    void advanceForwardUntilLine();
    void steerCenter();
    void pivotLookLeft();
    void pivotLookRight();

    // Concrete actions
    void stopAllComponents();
    bool advanceForwardUntilPointZone();
    void searchAndGrabBall();
    void goTo22Zone();

    String getCurrentColorName() {
        return _colorSensor->getCurrentColorName();
    }

    int getUltrasonicDistance() {
        return _ultrasonicSensor->getDistance();
    }

    bool isLineDetectedLeft() {
        return _lineFollowerSensor->isLineDetectedLeft();
    }

    bool isLineDetectedRight() {
        return _lineFollowerSensor->isLineDetectedRight();
    }

    void setBallIsInClaw() {
        _isBallInClaw = true;
    }

    void setBallIsInNotClaw() {
        _isBallInClaw = false;
    }
    
    bool isBallInClaw() {
        return _isBallInClaw;
    }

    void addFivePointsToScore() {
        _score += 5;
    }

    String getCurrentZone() {
        String currentColorName = _colorSensor->getCurrentColorName();
        String zoneName = "ERROR";
        if (currentColorName == "BLEU") zoneName = "Engagement";
        if (currentColorName == "BLANC") zoneName = "Centrale ou zone 22";
        if (currentColorName == "VERT") zoneName = "En but";
        _currentZone = zoneName;
        return zoneName;
    }

    int getCurrentZoneRow() {
        return _currentZoneRow;
    };

    void test() {
        // _colorSensor->getColorCode();
        _ultrasonicSensor->getDistance();
    }
private:
    Chassis* _chassis = nullptr;
    Arm* _arm = nullptr;
    Claw* _claw = nullptr;
    UltrasonicSensor* _ultrasonicSensor = nullptr;
    static UltrasonicSensor* _staticUltrasoundSensor;
    static bool checkObstacle();
    LineFollowerSensor* _lineFollowerSensor = nullptr;
    static LineFollowerSensor* _staticLineFollowerSensor;
    static bool checkLineDetection();

    ColorSensor* _colorSensor = nullptr;
    static ColorSensor* _staticColorSensor;
    static bool checkColorCode(double position);

    bool _isBallInClaw = false;
    int _score = 0;
    String _currentZone = "ERROR";
    int _currentZoneRow = 3;
    bool _isAlignedWithZones = true;
};

#endif
