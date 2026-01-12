#define CLAW_H
#ifdef CLAW_H

#include "MeMegaPiDCMotor.h"

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
        closeUntilLimit();
        Serial.println("Claw initialized, opening to limit");
        openUntilLimit();
    }

    void openDuringMs(int durationMs) {
        _motor->run(+100);
        delay(durationMs);
        stop();
    }

    void closeDuringMs(int durationMs) {
        _motor->run(-100);
        delay(durationMs);
        stop();
    }

    void openUntilLimit() {
        openDuringMs(3000);
    }

    void closeUntilLimit() {
        closeDuringMs(4000);
    }

    void stop() {
        _motor->stop();
    }
private:
    MeMegaPiDCMotor* _motor;
};

#endif