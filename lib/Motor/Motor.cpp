#include "Motor.h"
#include "Arduino.h"
#include "MeMegaPiDCMotor.h"


Motor::Motor(int port) : _port(port), _MeEncoder(NULL) {
}

void Motor::set_analogic_speed(int speed) {
    _current_analogic_speed = speed;
    _MeEncoder->setMotorPwm(speed);
}

void Motor::move_to(long angle, int speed) {
    _MeEncoder->moveTo(angle, speed);
}

void Motor::update() {
    _MeEncoder->loop(); 
}

float Motor::get_shaft_speed() {
    return (_motor_rpm * _current_analogic_speed) / 255.0f;
}

float Motor::get_final_speed() {
    return get_shaft_speed() * _gear_ratio;
}

void Motor::save_position_to_eeprom(int address) {
    long currentPos = _MeEncoder->getCurPos();
    EEPROM.put(address, currentPos);
}

void Motor::load_position_from_eeprom(int address) {
    long savedPos;
    EEPROM.get(address, savedPos);

    _MeEncoder->setPulsePos(savedPos);
}

long Motor::get_position() {
    if (_MeEncoder) {
        return _MeEncoder->getCurPos();
    }
    return 0;
}

void Motor::set_position(long pos) {
    if (_MeEncoder) {
        _MeEncoder->setPulsePos(pos);
    }
}