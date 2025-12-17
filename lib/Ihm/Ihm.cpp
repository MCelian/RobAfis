#include "Ihm.h"
#include "Arduino.h"

Ihm::Ihm(HardwareSerial* s) : _serial(s), _last_command_received('\0') {}

void Ihm::initialize(long baudrate) {
        _serial->begin(baudrate);
        println("IHM Initialized");
    }

void Ihm::print(const String& msg) {
    _serial->print(msg);
}

void Ihm::println(const String& msg) {
    _serial->println(msg);
}

char Ihm::readCommand() {
    if (_serial->available() > 0) {
        _last_command_received = (char)_serial->read();
        return _last_command_received;
    }
    return '\0';
}
//   unsigned long now = millis();

//   if (now - lastTime >= INTERVAL) {
//     lastTime = now;
//   }
//   robot.do_scenario_auto_test();