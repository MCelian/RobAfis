#include "Chassis.h"
#include "Motor.h"
#include "Gyroscope.h"
#include "math.h"

#define MAX_SPEED 150
#define STOP_SPEED 0

Chassis::Chassis(int motor_advance_port, int motor_steering_port, int gyroscope_port) {
    _motor_advance = new Motor(motor_advance_port);
    _motor_steering = new Motor(motor_steering_port);
    _gyroscope = new Gyroscope(gyroscope_port);
}

Chassis::~Chassis() {
    delete _motor_advance;
    delete _motor_steering;
    delete _gyroscope;
}

void Chassis::initialize() {
    _gyroscope->initialize();
}

void Chassis::forward() {
    _motor_advance->set_analogic_speed(MAX_SPEED);
}

void Chassis::backward() {
    _motor_advance->set_analogic_speed(-MAX_SPEED);
}

boolean Chassis::steer_to_angle(double target_angle) {
    unsigned long timeout_ms = 3000;
    int steer_speed = DEFAULT_STEER_SPEED;
    double tolerance_deg = STEER_ANGLE_MARGIN;
    unsigned long start = millis();
    while (millis() - start < timeout_ms) {
        update_sensors();
        double current = get_angle_z();
        double delta = target_angle - current;
        delta = fmod(delta + 540.0, 360.0) - 180.0; // normalize to [-180,180)
        if (fabs(delta) <= tolerance_deg) {
            stop_steering();
            return true;
        }
        int speed = (delta > 0) ? -steer_speed : steer_speed;
        _motor_steering->set_analogic_speed(speed);
        delay(10);
    }
    stop_steering();
    return false;
}

void Chassis::stop_movement() {
    _motor_advance->set_analogic_speed(STOP_SPEED);
}

void Chassis::stop_steering() {
    _motor_steering->set_analogic_speed(STOP_SPEED);
}

void Chassis::update_sensors() {
    _gyroscope->update();
}

double Chassis::get_angle_x() {
    return _gyroscope->get_angle_x();
}

double Chassis::get_angle_y() {
    return _gyroscope->get_angle_y();
}

double Chassis::get_angle_z() {
    return _gyroscope->get_angle_z();
}