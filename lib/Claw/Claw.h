#define CLAW_H
#ifdef CLAW_H

#include "MeMegaPiDCMotor.h"
#define PWM 100

class Claw {
public:
    Claw(int port) {
        _motor = new MeMegaPiDCMotor(port);
    };

    ~Claw() {
        delete _motor;
    }

    void initialize() {
        stop();
        openDuringMs(2000);
        closeUntilLimit();
    }

    void openDuringMs(int durationMs) {
        _motor->run(-PWM);
        delay(durationMs);
        stop();
    }

    void closeDuringMs(int durationMs) {
        _motor->run(+PWM);
        delay(durationMs);
        stop();
    }

    void openUntilLimit() {
        openDuringMs(3000);
    }

    void closeUntilLimit() {
        closeDuringMs(6000);
    }

    void stop() {
        _motor->stop();
    }
private:
    MeMegaPiDCMotor* _motor;
};

#endif