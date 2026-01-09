#include "Arduino.h"
#include "RobotFactory.h"
#include "Ihm.h"

Robot* robot = nullptr;
Ihm ihm(&Serial3);

void sendDataToIhm();

void setup() {
  Serial.begin(9600);
  ihm.initialize();

  robot = RobotFactory::createRugbyRobot();
  //robot->initializeChassis();
  //robot->initializeClaw();
  //robot->initializeArm();
  //robot->initializeUltrasonicSensor();
  //robot->initializeColorSensor();
  //robot->doScenarioAutoTest();
}

void loop() {
  char command = ihm.readCommand();
  switch (command)
  {
  case '0':
    ihm.println("Executing: Start");
    Serial.println("Executing: Start");
  break;
  
  case '1':
    ihm.println("Executing: Emergency Stop");
    Serial.println("Executing: Emergency Stop");
  break;

  case '2':
    ihm.println("Executing: Mechanical Emergency Stop");
    Serial.println("Executing: Mechanical Emergency Stop");
  break;

  case '3':
    ihm.println("Executing: Electric Emergency Stop");
    Serial.println("Executing: Electric Emergency Stop");
    robot->doEmergencyStop();
  break;

  case '4':
    ihm.println("Executing: Stop");
    Serial.println("Executing: Stop");
    robot->doEmergencyStop();
  break;
  
  case '5':
    ihm.println("Executing: Resume");
    Serial.println("Executing: Resume");
    robot->doEmergencyStop();
  break;

  case '6':
    ihm.println("Executing: Auto Test Scenario");
    Serial.println("Executing: Auto Test Scenario");
    robot->doScenarioAutoTest();
  break;

  case '7':
    ihm.println("Executing: Try Scenario");
    Serial.println("Executing: Try Scenario");
    robot->doScenarioTry();
  break;

  case '8':
    ihm.println("Executing: Conversion Scenario");
    Serial.println("Executing: Conversion Scenario");
    robot->doScenarioConversion();
  break;

  default:
    break;
  }
  
  sendDataToIhm();
}

void sendDataToIhm() {
    int color = robot->getColorData();
    String colorName = robot->getColorName();
    int distance = robot->getDistanceData();
    int lineSensorState = robot->getLineSensorData();
    bool isLineDetected = robot->isLineDetectedData();
    
    String data = "SENSOR_DATA|";
    data += "Color:" + colorName + "|";
    data += "Distance:" + String(distance) + "cm|";
    data += "LineSensor:" + String(lineSensorState) + "|";
    data += "LineDetected:" + String(isLineDetected ? "OUI" : "NON");
    
    ihm.println(data);
}