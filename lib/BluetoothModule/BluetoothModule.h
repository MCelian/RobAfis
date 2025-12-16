#ifndef BLUETOOTH_SENSOR_H
#define BLUETOOTH_SENSOR_H

#include <Arduino.h>
class MeBluetooth; // forward-declare

class BluetoothSensor {
public:
    BluetoothSensor(MeBluetooth* b);
    void init(long baud);
    int available();
    int read();
    String readString();
    void print(const char* s);
    void println(const char* s);
    void write(uint8_t b);
private:
    MeBluetooth* _b;
};

#endif // BLUETOOTH_SENSOR_H