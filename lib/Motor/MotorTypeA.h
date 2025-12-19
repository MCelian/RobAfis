#include "Motor.h"

class MotorTypeA : public Motor {
public:
    MotorTypeA(int slot) : Motor(slot) {
        setup_encoder(8, 46, 1.8, 0.05, 1.5, 0.18);
    }
};