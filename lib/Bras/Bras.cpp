#include "Bras.h"
#include <Arduino.h>

Bras::Bras(MeMegaPiDCMotor* motor, int vitesse_defaut)
{
    // Store the pointer to the motor object
    _moteurBras = motor;
    // Stockage de la vitesse par défaut dans la variable privée de la classe
    _vitesseDefaut = abs(vitesse_defaut);
}