#include "Robot.h"
#include "MeMegaPi.h" // The ONLY file to include this!
#include <Arduino.h>

// Define the ports for your motors here
#define BRAS_MOTOR_PORT PORT3B
#define CHASSIS_AVREC_MOTOR_PORT PORT1B
#define CHASSIS_GD_MOTOR_PORT PORT2B

// Declare motor objects as static so they are local to this file
static MeMegaPiDCMotor moteur_bras(BRAS_MOTOR_PORT);
static MeMegaPiDCMotor moteur_chassis_avrec(CHASSIS_AVREC_MOTOR_PORT);
static MeMegaPiDCMotor moteur_chassis_gd(CHASSIS_GD_MOTOR_PORT);

Robot::Robot() {
    // Create the robot parts, passing the motors to them
    _bras = new Bras(&moteur_bras);
    _chassis = new Chassis(&moteur_chassis_avrec, &moteur_chassis_gd);
}

Robot::~Robot() {
    delete _bras;
    delete _chassis;
}

// --- Implémentation des méthodes de contrôle ---

void Robot::avancer(int vitesse) {
    int vitesse_reelle = (vitesse == -1) ? _chassis->_vitesseARDefaut : abs(vitesse);
    _chassis->_moteurAvRec->run(vitesse_reelle);
}

void Robot::reculer(int vitesse) {
    int vitesse_reelle = (vitesse == -1) ? _chassis->_vitesseARDefaut : abs(vitesse);
    _chassis->_moteurAvRec->run(-vitesse_reelle);
}

void Robot::droite(int vitesse) {
    int vitesse_reelle = (vitesse == -1) ? _chassis->_vitesseDGDefaut : abs(vitesse);
    _chassis->_moteurGaucheDroite->run(vitesse_reelle);
}

void Robot::gauche(int vitesse) {
    int vitesse_reelle = (vitesse == -1) ? _chassis->_vitesseDGDefaut : abs(vitesse);
    _chassis->_moteurGaucheDroite->run(-vitesse_reelle);
}

void Robot::arreterAvancement() {
    _chassis->_moteurAvRec->run(0);
}

void Robot::arreterDirection() {
    _chassis->_moteurGaucheDroite->run(0);
}

void Robot::leverBras(int vitesse) {
    int vitesse_reelle = (vitesse == -1) ? _bras->_vitesseDefaut : abs(vitesse);
    _bras->_moteurBras->run(vitesse_reelle);
}

void Robot::baisserBras(int vitesse) {
    int vitesse_reelle = (vitesse == -1) ? _bras->_vitesseDefaut : abs(vitesse);
    _bras->_moteurBras->run(-vitesse_reelle);
}

void Robot::arreterBras() {
    _bras->_moteurBras->run(0);
}
