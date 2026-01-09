#ifndef IHM_H
#define IHM_H

#include "HardwareSerial.h"

class Ihm {
public:
    Ihm(HardwareSerial* serial);
    void initialize();
    void print(const String& msg);
    void println(const String& msg);
    char readCommand();
    String writeCommand(const String& command);
    static const String ESSAI;
    static const String BALLON1;

private:
    HardwareSerial* _serial;
    char _last_command_received;
};

#endif
