#ifndef CHASSIS_H
#define CHASSIS_H

// Forward-declare the motor class instead of including the full header.
class MeMegaPiDCMotor;

class Chassis {
    public:
        // The constructor now accepts pointers to the motor objects.
        Chassis(MeMegaPiDCMotor* motor_av_rec, MeMegaPiDCMotor* motor_gauche_droite, int vitesse_ar_defaut = 150, int vitesse_dg_defaut = 200);

    private:
        friend class Robot; // Allow Robot class to access private members
        MeMegaPiDCMotor* _moteurAvRec;
        MeMegaPiDCMotor* _moteurGaucheDroite;
        int _vitesseARDefaut;
        int _vitesseDGDefaut;
};

#endif // CHASSIS_H
