#include "Arduino.h"
#include "RobotFactory.h"

#include "MeEncoderOnBoard.h"
#include "Motor.h"
Robot* myRobot = nullptr;

void setup() {
  Serial.begin(9600);
  myRobot = RobotFactory::createRugbyRobot();
  myRobot->initializeChassis();
}

void loop() {
  myRobot->doScenarioTry();
}