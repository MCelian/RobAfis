#ifndef BRAS_H
#define BRAS_H

// Forward declare the MeMegaPiDCMotor class instead of including the full header.
// This avoids including MeMegaPi.h here, which is likely the source of the "multiple definition" errors.
class MeMegaPiDCMotor;

class Bras {
    public:
        // The constructor now accepts a pointer to the motor object.
        Bras(MeMegaPiDCMotor* motor, int vitesse_defaut = 100);

    private:
        friend class Robot; // Allow Robot class to access private members
        MeMegaPiDCMotor* _moteurBras;
        int _vitesseDefaut;
};

#endif // BRAS_H