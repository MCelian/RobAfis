#include "IhmRobotFacade.h"

#define START_COMMAND_ID '0'
#define EMERGENCY_STOP_ID '1'
#define MECHANIC_EMERGENCY_STOP_ID '2'
#define ELECTRIC_EMERGENCY_STOP_ID '3'
#define STOP_ID '4'
#define RESUME_ID '5'
#define SCENARIO_AUTO_TEST_ID '6'
#define SCENARIO_TRY_ID '7'
#define SCENARIO_CONVERSION_ID '8'

void IhmRobotFacade::executeIhmCommand(int command) {
    switch (command) {
        case START_COMMAND_ID:
            _ihm->println("Executing: Start");
        break;

        case EMERGENCY_STOP_ID:
            _ihm->println("Executing: Emergency Stop");
        break;

        case MECHANIC_EMERGENCY_STOP_ID:
            _ihm->println("Executing: Mechanical Emergency Stop");
        break;

        case ELECTRIC_EMERGENCY_STOP_ID:
            _ihm->println("Executing: Electric Emergency Stop");
            _robot->doEmergencyStop();
        break;

        case STOP_ID:
            _ihm->println("Executing: Stop");
            _robot->doEmergencyStop();
        break;

        case RESUME_ID:
            _ihm->println("Executing: Resume");
            _robot->doEmergencyStop();
        break;

        case SCENARIO_AUTO_TEST_ID:
            _ihm->println("Executing: Auto Test Scenario");

            _robot->advanceForwardUntilObstacle();
            _robot->openClawDuringM(3000);
            _robot->moveArmToGrabPosition();
            _robot->closeClawDuringMs(6000);
            
            _ihm->setBallIsInClaw();

            _robot->moveArmToNeutralPosition();
            
            _robot->advanceFowardUntilPointZone();

;           _ihm->addFivePointsToScore();
        break;

        case SCENARIO_TRY_ID:
            _ihm->println("Executing: Try Scenario");
        break;

        case '8':
            _ihm->println("Executing: Conversion Scenario");
        break;

        default:
        break;
    }
}

void IhmRobotFacade::sendRobotDataToIhm() {
    String colorName = _robot->getColorName();
    int distance = _robot->getDistanceData();
    int lineSensorState = _robot->getLineSensorData();
    bool isLineDetected = _robot->isLineDetectedData();
    
    String data = "-----------------------\n";
    data += "SENSOR_DATA\n";
    data += "-----------------------\n";
    data += "Color: " + colorName + "\n";
    data += "Distance: " + String(distance) + " cm\n";
    data += "LineSensor: " + String(lineSensorState) + "\n";
    data += "LineDetected: " + String(isLineDetected ? "OUI" : "NON");
    data += "\n";
    data += "-----------------------\n";
    data += "\n";
    
    _ihm->println(data);
}