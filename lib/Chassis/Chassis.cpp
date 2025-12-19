#include "Chassis.h"
#include "Motor.h"
#include <EEPROM.h>

#define MAX_SPEED 255
#define STOP_SPEED 0
    
Chassis::Chassis(Motor* motor_advance, Motor* motor_steering)
{
    _motor_advance = motor_advance;
    _motor_steering = motor_steering;
}

void Chassis::forward() {
    _motor_advance->set_analogic_speed(MAX_SPEED);
}

void Chassis::backward() {
    _motor_advance->set_analogic_speed(-MAX_SPEED);
}

void Chassis::align_left() {
    _motor_steering->move_to(-150, 150);
    save_steering_pos();
}

void Chassis::align_right() {
    _motor_steering->move_to(150, 150);
    save_steering_pos();
}

void Chassis::align_center() {
    _motor_steering->move_to(0, 150);
    save_steering_pos();
}

void Chassis::save_steering_pos() {
    long pos = _motor_steering->get_position();
    EEPROM.put(4, pos); // Adresse 4 pour la direction
}

void Chassis::stop_movement() {
    _motor_advance->set_analogic_speed(STOP_SPEED);
}

void Chassis::stop_steering() {
    _motor_steering->set_analogic_speed(STOP_SPEED);
}

void Chassis::update_motors() {
    _motor_advance->update();
    _motor_steering->update();
}

void Chassis::save_steering_pos() {
    long pos = _motor_steering->get_position();
    EEPROM.put(4, pos); 
}