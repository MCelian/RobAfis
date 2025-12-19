#ifndef MOTOR_H
#define MOTOR_H

#include "MeMegaPi.h"
#include "EEPROM.h"

class MeMegaPiDCMotor;

class Motor {
public:
    Motor(int port) : _port(port) {}
    virtual ~Motor() {}
    void set_motor_rpm();
    void set_motor_voltage();
    void set_gear_ratio();
    void set_analogic_speed(int speed);
    void move_to(long angle, int speed);
    void update();
    float get_shaft_speed();
    float get_final_speed();
    long get_position();
    void set_position(long pos);
    void save_position_to_eeprom(int address);
    void load_position_from_eeprom(int address);

protected:
    MeEncoderOnBoard* _MeEncoder;
    int _port;

    void setup_encoder(int pulse, int ratio, float posP, float posI, float posD, float speedP) {
        _MeEncoder = new MeEncoderOnBoard(_port);
        _MeEncoder->setPulse(pulse);
        _MeEncoder->setRatio(ratio);
        _MeEncoder->setPosPid(posP, posI, posD);
        _MeEncoder->setSpeedPid(speedP, 0, 0);
    }
    

private:
    int _motor_rpm;
    int _motor_voltage;
    int _current_analogic_speed;
    float _gear_ratio;
    int _port;
};

#endif