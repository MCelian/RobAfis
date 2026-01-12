#ifndef IHM_H
#define IHM_H

#include "HardwareSerial.h"

class Ihm {
public:
    Ihm(HardwareSerial* serial);
    void initialize();

    char readCommand();

    void setBallIsInClaw() {
        println(BALLISNOTINCLAW);
        _isBallInClaw = true;
    }

    void setBallIsNotInClaw() {
        println(BALLISINCLAW);
        _isBallInClaw = false;
    }

    void addFivePointsToScore() {
        println(TRYSUCCESFUL);
        _score += 5;
    }

    void print(const String& msg);
    void println(const String& msg);
private:
    HardwareSerial* _serial;
    char _last_command_received;
    bool _isBallInClaw = false;
    int _score = 0;
    
    // IHM command constants
    const char* TRYSUCCESFUL = "POINT5 5";
    const char* BALLISINCLAW = "Ballon 0";
    const char* BALLISNOTINCLAW = "Ballon 1";
};

#endif
