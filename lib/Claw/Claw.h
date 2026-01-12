#define CLAW_H
#ifdef CLAW_H

#include "MeMegaPiDCMotor.h"

class Claw {
public:
    Claw(int port) {
        _motor = new MeMegaPiDCMotor(port);
        stop();
    };

    ~Claw() {
        delete _motor;
    }

    void openDuringMs(int durationMs) {
        _motor->run(-100);
        delay(durationMs);
        stop();
    }

    void closeDuringMs(int durationMs) {
        _motor->run(100);
        delay(durationMs);
        stop();
    }

    void openUntilLimit() {
        openDuringMs(6000);
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