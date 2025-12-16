#include "Arduino.h"
#include "Robot.h"

#define BT Serial3  // Bluetooth sur MegaPi
unsigned long lastTime = 0;
const unsigned long INTERVAL = 500; 

Robot robot;

void setup() {
  Serial.begin(9600);
  BT.begin(115200);
  Serial.println("MegaPi demarre");
  BT.println("MegaPi demarre");
  robot.initialize_sensors();
}

void loop() {
  // unsigned long now = millis();

  // if (now - lastTime >= INTERVAL) {
  //   lastTime = now;
  // }
  // robot.do_scenario_auto_test();
  robot.do_scenario_auto_test();
}