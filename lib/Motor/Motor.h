#ifndef MOTOR_H
#define MOTOR_H

#include "MeEncoderOnBoard.h"

class Motor {
public:
    Motor(int port, void (*isr_callback)(void), float additionnalRatio = 1.0, double pidP = 18.0, double pidI = 0, double pidD = 6.0);
    
    // Public method to be called BY the ISR
    void handleInterrupt(); 

    // Your movement methods
    void setCurrentPositionAsZero() { _encoder.setPulsePos(0); }
    long moveUntilStall(int pwmPower, int minPulsesPerSampleTime, unsigned long timeoutMs, bool (*stopCondition)() = nullptr);
    void moveToPosition(long targetPos, int speed = 100);
    long getPulsePos() { return _encoder.getPulsePos(); }

private:
    MeEncoderOnBoard _encoder;
    int _port;

    // Static pointer needed for the ISR
    static Motor* instance;

    // 2. The static "Trampoline" function for attachInterrupt
    static void executeISR();

    // 3. The actual logic function (Member function)
    void updatePulse();
};

#endif
