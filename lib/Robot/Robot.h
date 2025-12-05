#ifndef ROBOT_H
#define ROBOT_H

#include "Bras.h"
#include "Chassis.h"

class Robot {
public:
    Robot();
    ~Robot();

    // --- Méthodes de contrôle du Châssis ---
    void avancer(int vitesse = -1);
    void reculer(int vitesse = -1);
    void droite(int vitesse = -1);
    void gauche(int vitesse = -1);
    void arreterAvancement();
    void arreterDirection();

    // --- Méthodes de contrôle du Bras ---
    void leverBras(int vitesse = -1);
    void baisserBras(int vitesse = -1);
    void arreterBras();

private:
    Bras* _bras;
    Chassis* _chassis;
};

#endif // ROBOT_H