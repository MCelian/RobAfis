#include "Ihm.h"
#include "Arduino.h"

Ihm::Ihm(HardwareSerial* s) : _serial(s), _last_command_received('\0') {}

void Ihm::initialize(long baudrate) {
        _serial->begin(baudrate);
        println("IHM Initialized");
    }

void Ihm::print(const String& msg) {
    if (msg.length() == 0) return;
    _serial->print(msg);
    delay(10);
}

void Ihm::println(const String& msg) {
    _serial->println(msg);
    delay(10);
}

char Ihm::readCommand() {
    if (_serial->available() > 0) {
        _last_command_received = (char)_serial->read();
        return _last_command_received;
    }
    else {
        return _last_command_received;
    }
    return '\0';
}
//   unsigned long now = millis();

//   if (now - lastTime >= INTERVAL) {
//     lastTime = now;
//   }
//   robot.do_scenario_auto_test();