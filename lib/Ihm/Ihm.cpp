#include "Ihm.h"
#include "Arduino.h"

Ihm::Ihm(HardwareSerial* s) : _serial(s), _last_command_received('\0') {}

void Ihm::initialize() {
    long baudrate = 115200;
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

String Ihm::writeCommand(const String& command) {
    println(command);
    delay(50); // Wait for the command to be processed
    
    // Switch-like logic for different commands
    if (command == ESSAI) {
        // Case: ESSAI (POINT5 5)
        println("ESSAI MARQUE!");
    } else if (command == BALLON1) {
        // Case: BALLON1 (Ballon 1)
        println("Ballon attrape!");
    } else {
        // Default case: read response
        String response = "";
        while (_serial->available() > 0) {
            char c = (char)_serial->read();
            response += c;
            delay(5); // Small delay to allow more data to arrive
        }
        return response;
    }
    return "";
}
