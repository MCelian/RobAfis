#include "Bluetooth.h"
#include <Arduino.h>

BluetoothSensor::BluetoothSensor(MeBluetooth* b) : _b(b) {}

void BluetoothSensor::init(long baud) {
    _b->begin(baud);
}

int BluetoothSensor::available() {
    return _b->available();
}

int BluetoothSensor::read() {
    return _b->read();
}

String BluetoothSensor::readString() {
    String s;
    while (_b->available()) {
        char c = (char)_b->read();
        s += c;
    }
    return s;
}

void BluetoothSensor::print(const char* s) {
    const char* p = s;
    while (*p) {
        _b->write((uint8_t)*p++);
    }
    Serial.print(s);
}

void BluetoothSensor::println(const char* s) {
    print(s);
    _b->write((uint8_t)'\r');
    _b->write((uint8_t)'\n');
    Serial.println(s);
}

void BluetoothSensor::write(uint8_t b) {
    _b->write(b);
    Serial.write(b);
}