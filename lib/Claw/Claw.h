#define CLAW_H
#ifdef CLAW_H

#include "MeMegaPiDCMotor.h"

class Claw {
public:
    Claw(int port) { _motor = new MeMegaPiDCMotor(port); };
    ~Claw() { delete _motor; }
    void open() { _motor->run(-100); }
    void close() { _motor->run(100); }
    void stop() { _motor->stop(); }
private:
    MeMegaPiDCMotor* _motor;
};

#endif