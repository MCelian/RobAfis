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
    
    void initialize() {
        initializeComponent(_ultrasonicSensor);
        //initializeComponent(_claw);
        initializeComponent(_arm);
        //initializeComponent(_chassis);
    }

    void advanceForwardUntilObstacle();
    void openClawDuringM(int durationMs);
    void closeClawDuringMs(int durationMs);

    void moveArmToGrabPosition();
    void moveArmToNeutralPosition();

    void advanceFowardUntilPointZone();

    void stopAllComponents();

    String getSensorDataToString();
private:
    Chassis* _chassis = nullptr;
    Arm* _arm = nullptr;
    Claw* _claw = nullptr;
    UltrasonicSensor* _ultrasonicSensor = nullptr;
    static UltrasonicSensor* _staticSensor;
    static bool checkObstacle();
    LineFollowerSensor* _lineFollowerSensor = nullptr;
    ColorSensor* _colorSensor = nullptr;

    void pivotLookLeft();
    void pivotLookRight();
    void realignCenter();
};

#endif