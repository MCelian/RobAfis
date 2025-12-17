#include "Ihm.h"
#include "Arduino.h"

Ihm::Ihm(HardwareSerial* s) : _serial(s), _last_command_received('\0') {}

void Ihm::initialize(long baudrate) {
        _serial->begin(baudrate);
        println("IHM Initialized");
    }

void Ihm::print(const String& msg) {
    unsigned long now = millis();
    if (now - _ihm_last_print_ms >= 1000UL) {
        _serial->print(msg);
        _ihm_last_print_ms = now;
    }
}

void Ihm::println(const String& msg) {
    unsigned long now = millis();
    if (now - _ihm_last_print_ms >= 1000UL) {
        _serial->println(msg);
        _ihm_last_print_ms = now;
    }
}

char Ihm::readCommand() {
    if (_serial->available() > 0) {
        _last_command_received = (char)_serial->read();
    }
    return _last_command_received;
}