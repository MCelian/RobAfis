#include "Chassis.h"
#include <Arduino.h>

Chassis::Chassis(MeMegaPiDCMotor* motor_av_rec, MeMegaPiDCMotor* motor_gauche_droite, int vitesse_ar_defaut, int vitesse_dg_defaut)
{
    // Store the pointers to the motor objects
    _moteurAvRec = motor_av_rec;
    _moteurGaucheDroite = motor_gauche_droite;
    // Stockage des vitesses par défaut dans les variables privées de la classe
    _vitesseARDefaut = abs(vitesse_ar_defaut); // Assurez-vous qu'elle est positive
    _vitesseDGDefaut = abs(vitesse_dg_defaut); // Assurez-vous qu'elle est positive
}