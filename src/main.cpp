#include <Arduino.h>
#include "Robot.h" // On inclut uniquement la classe principale Robot

// On crée une seule instance de notre Robot.
// C'est le constructeur de Robot qui s'occupera de créer le châssis et le bras.
Robot robot;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // On contrôle le robot via ses méthodes de haut niveau.
  robot.avancer();
  delay(2000);
  robot.arreterAvancement();
  delay(1000);
  robot.reculer(100);
  delay(2000);
  robot.arreterAvancement();
  delay(1000);
  robot.droite();
  delay(2000);
  robot.arreterDirection();
  delay(1000);
  robot.gauche(100);
  delay(2000);
  robot.arreterDirection();
  delay(3000);

  robot.leverBras();
  delay(2000);
  robot.arreterBras();
}
