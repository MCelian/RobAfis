#include "Motor.h"

Motor* Motor::instance = nullptr;

Motor::Motor(int port, void (*isrCallback)(void), float additionnalRatio, double pidP, double pidI, double pidD) : _encoder(port) {
    _encoder.reset(port);
    attachInterrupt(_encoder.getIntNum(), isrCallback, RISING);
    additionnalRatio == 1.0 ? _encoder.setRatio(39.267) : _encoder.setRatio(39.267 * additionnalRatio);
    _encoder.setPosPid(pidP, pidI, pidD);
}

void Motor::handleInterrupt() {
    if (digitalRead(_encoder.getPortB()) == 0) {
        _encoder.pulsePosMinus();
    } else {
        _encoder.pulsePosPlus();
    }
}

long Motor::moveUntilStall(int pwmPower, int minPulsesPerSampleTime, unsigned long timeoutMs, bool (*stopCondition)()) {
    _encoder.setTarPWM(pwmPower);

    long startTime = millis();
    long lastCheckTime = millis();
    long lastPulsePosition = _encoder.getPulsePos();

    _encoder.setMotorPwm(pwmPower);

    // Motor Startup Delay
    while(millis() - startTime < 500) {
        _encoder.loop();
    }

    // Motor Concrete Movement
    while(millis() - startTime < timeoutMs) {
        _encoder.loop();

        // --- NEW: External Stop Check ---
        if (stopCondition != nullptr && stopCondition()) {
            Serial.println("External Stop Condition Met!");
            _encoder.setMotorPwm(0);
            _encoder.setTarPWM(0);
            return _encoder.getCurPos();
        }

        int sampleTime = 100;
        if (millis() - lastCheckTime > sampleTime) {
            long currentPulsePosition = _encoder.getPulsePos();
            long currentPulsesPerSampleTime = abs(currentPulsePosition - lastPulsePosition);
            Serial.print("Pulses in last ");
            Serial.println(currentPulsesPerSampleTime);
            if (currentPulsesPerSampleTime < minPulsesPerSampleTime) {
                Serial.println("STALL DETECTED! (Pulses stopped changing)");
                _encoder.setMotorPwm(0);
                _encoder.setTarPWM(0);
                return _encoder.getCurPos();
            }
            lastPulsePosition = currentPulsePosition;
            lastCheckTime = millis();
        }
    }

    Serial.println("Timeout Reached");
    _encoder.setMotorPwm(0);
    _encoder.setTarPWM(0);
    return _encoder.getCurPos();
}

void Motor::moveToPosition(long targetPosition, int speed = 100) {
    _encoder.moveTo(targetPosition, speed);

    int timeoutMs = 3000;
    unsigned long startTime = millis();

    while(!_encoder.isTarPosReached() && (millis() - startTime < timeoutMs)) {
        _encoder.loop();
    }

    // Disable the built-in PID for a moment so we can drive manually
    _encoder.setTarPWM(0);
    
    long error = targetPosition - _encoder.getCurPos();
    
    while (abs(error) > 1) {
        _encoder.loop();

        int aggressivity = 4; // Higher values = more aggressive response
        int power = error * aggressivity;

        // Minimum Power Threshold
        if (power > 0 && power < 60) power = 60;
        if (power < 0 && power > -60) power = -60;
        
        // Power Limit
        power = constrain(power, -150, 150);
        
        _encoder.setMotorPwm(power);        
        error = targetPosition - _encoder.getCurPos();
    }
    
    _encoder.setMotorPwm(0);
}