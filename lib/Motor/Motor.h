#ifndef MOTOR_H
#define MOTOR_H

class MeMegaPiDCMotor;

class Motor {
public:
    Motor(int port);
    void set_motor_rpm();
    void set_motor_voltage();
    void set_gear_ratio();
    void set_analogic_speed(int speed);
    float get_shaft_speed();
    float get_final_speed();

private:
    MeMegaPiDCMotor* _MeMotor;
    int _motor_rpm;
    int _motor_voltage;
    int _current_analogic_speed;
    float _gear_ratio;
    int _port;
};

#endif