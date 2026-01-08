#ifndef ROBOT_H
#define ROBOT_H

#include "Chassis.h"
#include "Arm.h"
#include "Claw.h"
#include "UltrasonicSensor.h"
#include "LineFollowerSensor.h"

class Robot {
public:
    Robot() { _chassis = nullptr; _arm = nullptr; _ultrasonicSensor = nullptr; _lineFollowerSensor = nullptr; }
    ~Robot() { delete _arm; delete _chassis; delete _ultrasonicSensor; delete _lineFollowerSensor; }
    void setChassis(Chassis* chassis) { delete _chassis; _chassis = chassis; };
    void setArm(Arm* arm) { delete _arm; _arm = arm; };
    void setClaw(Claw* claw) { delete _claw; _claw = claw; }
    void setUltrasonicSensor(UltrasonicSensor* sensor) { delete _ultrasonicSensor; _ultrasonicSensor = sensor; }
    void setLineFollowerSensor(LineFollowerSensor* sensor) { delete _lineFollowerSensor; _lineFollowerSensor = sensor; }
    void initializeChassis() { _chassis->findSteeringLimits(); }
    void doScenarioAutoTest();
    void doScenarioTry();
    void doScenarioConversion();
    void doEmergencyStop();

private:
    Chassis* _chassis;
    Arm* _arm;
    Claw* _claw;
    UltrasonicSensor* _ultrasonicSensor;
    LineFollowerSensor* _lineFollowerSensor;
};

#endif