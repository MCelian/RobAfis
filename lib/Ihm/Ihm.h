#ifndef IHM_H
#define IHM_H

#include "HardwareSerial.h"

class Ihm {
public:
    Ihm(HardwareSerial* s);
    void initialize(long baudrate);
    void print(const String& msg);
    void println(const String& msg);
    void print(const String& msg, unsigned long minIntervalSeconds);
    void println(const String& msg, unsigned long minIntervalSeconds);
    char readCommand();
private:
    HardwareSerial* _serial;
    char _last_command_received;
    unsigned long _ihm_last_print_ms; // moved here as an instance variable
};

#endif
