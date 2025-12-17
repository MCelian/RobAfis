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

void send_data_ihm() {
  ihm.println(robot.get_robot_data());
}

void loop() {
  robot.chassis()->update_sensors();
  char command = ihm.readCommand();
  Serial.println(command);
  delay(100);
  switch (command) {
    case '0':
    break;
    
    case '1':
      ihm.println("Executing: Emergency Stop");
      robot.do_emergency_stop();
    break;

    case '2':
      ihm.println("Executing: Emergency Stop MECHANIC");
      robot.do_emergency_stop();
    break;

    case '3':
      ihm.println("Executing: Emergency Stop ELECTRIC");
      robot.do_emergency_stop();
    break;

    case '4':
      ihm.println("Executing: Pause");
      robot.do_pause();
    break;
    
    case '5':
      ihm.println("Executing: Resume");
      robot.do_resume();
    break;

    case '6':
      ihm.println("Executing: Auto Test Scenario");
      robot.do_scenario_auto_test();
    break;

    case '7':
      ihm.println("Executing: Try Scenario");
      robot.do_scenario_try();
    break;

    case '8':
      ihm.println("Executing: Conversion Scenario");
      robot.do_scenario_conversion();
    break;

    default:
    break;
  }
  send_data_ihm();
}