#include "Motor.h"
#include "Arduino.h"
#include "MeMegaPiDCMotor.h"

Motor::Motor(int port)
{
    _MeMotor = new MeMegaPiDCMotor(port);
    _current_analogic_speed = 0;
    _port = port;
}

void Motor::set_analogic_speed(int speed) {
    _current_analogic_speed = speed;
    _MeMotor->run(speed);
}

float Motor::get_shaft_speed() {
    return (_motor_rpm * _current_analogic_speed) / 255.0f;
}

float Motor::get_final_speed() {
    return get_shaft_speed() * _gear_ratio;
}