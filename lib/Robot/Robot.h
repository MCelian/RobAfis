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
    void setChassis(Chassis* chassis) { delete _chassis; _chassis = chassis; };
    void setArm(Arm* arm) { delete _arm; _arm = arm; };
    void setClaw(Claw* claw) { delete _claw; _claw = claw; }
    void setUltrasonicSensor(UltrasonicSensor* sensor) { delete _ultrasonicSensor; _ultrasonicSensor = sensor; }
    void setLineFollowerSensor(LineFollowerSensor* sensor) { delete _lineFollowerSensor; _lineFollowerSensor = sensor; }
    void setColorSensor(ColorSensor* sensor) { delete _colorSensor; _colorSensor = sensor; }
    void initializeChassis() { _chassis->findSteeringLimits(); }
    void initializeArm() { _arm->initialize(); }
    void initializeClaw() { _claw->stop(); _claw->close(); delay(5000); _claw->stop(); }
    void initializeUltrasonicSensor() { _ultrasonicSensor->initialize(); }
    void initializeColorSensor() { _colorSensor->initialize(); }
    void doScenarioAutoTest();
    void doScenarioTry();
    void doScenarioConversion();
    void doEmergencyStop();

    void lineDetectedCountIncrement() { _lineDetectedCount++; }
    void lineDetectedCountDecrement() { _lineDetectedCount--; }
    void lineDetectedCountReset() { _lineDetectedCount = 0; }

    int getColorData() { return _colorSensor->getColor(); }
    int getDistanceData() { return _ultrasonicSensor->getDistance(); }
    int getLineSensorData() { return _lineFollowerSensor->readSensors(); }
    bool isLineDetectedData() { return _lineFollowerSensor->isLineDetected(); }
    String getColorName() { return _colorSensor->getCurrentColorName(); }
    void getRobotData();
private:
    Chassis* _chassis;
    Arm* _arm;
    Claw* _claw;
    UltrasonicSensor* _ultrasonicSensor;
    LineFollowerSensor* _lineFollowerSensor;
    ColorSensor* _colorSensor;
    int _lineDetectedCount = 0;

    void pivotLookLeft();
    void pivotLookRight();
    void realignCenter();
    int _distLeft = 0;
    int _distCenter = 0;
    int _distRight = 0;
};

#endif