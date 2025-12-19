#include "Arduino.h"
#include "Robot.h"
#include "Ihm.h"

Robot robot;
Ihm ihm(&Serial3);

void setup() {
  Serial.begin(9600);
  ihm.initialize(115200);
  robot.initialize_sensors();
}

void loop() {
  robot.chassis()->update_motors();
  char command = ihm.readCommand();
  switch (command)
  {
  case '0':
  break;
  
  case '1':
    
  break;

  case '2':
    
  break;

  case '3':
    
  break;

  case '4':
    ihm.println("Executing: Emergency Stop");
    robot.do_emergency_stop();
  break;
  
  case '5':
    
  break;

  case '6':
    ihm.println("Executing: Auto Test Scenario");
    robot.do_scenario_auto_test();
  break;

  default:
    break;
  }
}