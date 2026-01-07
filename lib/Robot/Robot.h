#ifndef ROBOT_H
#define ROBOT_H

#include "Chassis.h"
#include "Arm.h"
#include "Claw.h"
#include "UltrasonicSensor.h"

class Robot {
public:
    Robot();
    ~Robot();
    void setChassis(Chassis* chassis);
    void setArm(Arm* arm);
    void setClaw(Claw* claw);
    void setUltrasonicSensor(UltrasonicSensor* sensor);
    void doScenarioAutoTest();
    void doScenarioTry();
    void doScenarioConversion();
    void doEmergencyStop();

private:
    Chassis* _chassis;
    Arm* _arm;
    Claw* _claw;
    UltrasonicSensor* _ultrasonicSensor;
};

#endif