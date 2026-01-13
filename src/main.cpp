#include "Arduino.h"
#include "MeMegaPi.h"
#include "RobotFactory.h"
#include "IhmRobotFacade.h"
#include "Ihm.h"

#include <avr/wdt.h>

Robot* robot = nullptr;
Ihm* ihm = nullptr;
IhmRobotFacade* ihmRobotFacade = nullptr;

void sendDataToIhm();

void resetCard() {
  wdt_enable(WDTO_15MS);
  while (1) {}
}

void setup() {
  // resetCard();
  Serial.begin(9600);
  ihm = new Ihm(&Serial3);
  
  robot = RobotFactory::createRugbyRobot();
  robot->initialize();

  ihmRobotFacade = new IhmRobotFacade(ihm, robot);
}

void loop() {
  ihm->initialize();
  char command = ihm->readCommand();
  // ihmRobotFacade->test();
  ihmRobotFacade->sendRobotDataToIhm();
  ihmRobotFacade->executeIhmCommand(command);
}
