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

void IhmRobotFacade::executeIhmCommand(char command) {
    // Serial.print("command: ");
    // Serial.println(command);
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
            _robot->stopAllComponents();
        break;

        case STOP_ID:
            _ihm->println("Executing: Stop");
            _robot->stopAllComponents();
        break;

        case RESUME_ID:
            _ihm->println("Executing: Resume");
            executeIhmCommand(_ihm->lastExecutedCommand);
        break;

        case SCENARIO_AUTO_TEST_ID:
            _ihm->println("Executing: Auto Test Scenario");

            if (!_robot->isBallInClaw()) {
                _robot->advanceForwardUntilObstacle();

                _robot->openClawUntilLimit();
                _robot->moveArmToGrabPosition();
                _robot->closeClawUntilLimit();
                _ihm->setBallIsInClaw();
                _robot->setBallIsInClaw();
            }

            _robot->moveArmToNeutralPosition();

            // bool arrivedAtPointZone = _robot->advanceForwardUntilPointZone();
            // if (arrivedAtPointZone) {
            //     _ihm->addFivePointsToScore();
            // }
            _robot->advanceForwardUntilLine();
            _robot->advanceForwardUntilLine();
            _robot->advanceForwardUntilLine();
            _robot->advanceBackwardDuringMs(5000);

            _robot->moveArmToGrabPosition();

            _ihm->println("FIN");
        break;

        case SCENARIO_TRY_ID:
            _ihm->println("Executing: Try Scenario");

            _robot->advanceForwardUntilObstacle();

            _robot->pivotLookLeft();
            _robot->steerCenter();
            _robot->pivotLookRight();
            _robot->steerCenter();
        break;

        case SCENARIO_CONVERSION_ID:
            _ihm->println("Executing: Conversion Scenario");

            if (!_robot->isBallInClaw()) {
                _robot->advanceForwardUntilObstacle();

                _robot->openClawUntilLimit();
                _robot->moveArmToGrabPosition();
                _robot->closeClawUntilLimit();
                _robot->moveArmToNeutralPosition();
                _ihm->setBallIsInClaw();
                _robot->setBallIsInClaw();
            }

            // turnAround();
            _robot->pivotLookLeft();
            _robot->advanceForwardDuringMs(3000);
            _robot->steerCenter();
            _robot->advanceBackwardDuringMs(3000);
            
            _robot->pivotLookLeft();
            _robot->advanceForwardDuringMs(3000);
            _robot->steerCenter();
            _robot->advanceBackwardDuringMs(3000);
        break;

        default:
            Serial.println("RIEN FAIRE");
            return;
        break;
    }
}

void IhmRobotFacade::sendRobotDataToIhm() {
    String colorName = _robot->getCurrentColorName();
    int distance = _robot->getUltrasonicDistance();
    bool isLineDetectedLeft = _robot->isLineDetectedLeft();
    bool isLineDetectedRight = _robot->isLineDetectedRight();
    bool isLineDetected = isLineDetectedLeft || isLineDetectedRight;
    
    String data = "-----------------------\n";
    data += "SENSOR_DATA\n";
    data += "-----------------------\n";
    data += "Zone: " + _robot->getCurrentZone() + "\n";
    _ihm->println(data);
    data += "Ultrasound Distance: " + String(distance) + " cm\n";
    _ihm->println(data);

    data += "Is Line LEFT Detected: " + String(isLineDetectedLeft ? "OUI" : "NON") + "\n";
    data += "Is Line RIGHT Detected: " + String(isLineDetectedRight ? "OUI" : "NON") + "\n";
    data += "Is Line Detected: " + String(isLineDetected ? "OUI" : "NON") + "\n";
    _ihm->println(data);
    
    data += "-----------------------\n";
    data += "\n";

    _ihm->println(data);
}
