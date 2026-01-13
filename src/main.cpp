#include "Arduino.h"
#include "MeMegaPi.h"
#include "RobotFactory.h"
#include "IhmRobotFacade.h"
#include "Ihm.h"

Robot* robot = nullptr;
Ihm* ihm = nullptr;
IhmRobotFacade* ihmRobotFacade = nullptr;

void sendDataToIhm();

void setup() {
  Serial.begin(9600);
  ihm = new Ihm(&Serial3);
  ihm->initialize();
  
  robot = RobotFactory::createRugbyRobot();
  robot->initialize();

  ihmRobotFacade = new IhmRobotFacade(ihm, robot);
}

void loop() {
  ihm->reconnectIfNeeded();
  char command = ihm->readCommand();
  ihmRobotFacade->executeIhmCommand(command);
}
