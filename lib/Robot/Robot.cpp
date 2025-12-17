#include "Robot.h"
#include "MeMegaPi.h" // The ONLY file to include this!
#include "Wire.h"
#include "UltrasonicSensor.h"
#include "Ihm.h"
#include "ColorSensor.h"

static MeLineFollower line_follower(LINE_FOLLOWER_SENSOR_PORT);
static MeColorSensor color_sensor(COLOR_SENSOR_PORT);
static MeGyro gyro_sensor(GYRO_SENSOR_PORT);
static MeUltrasonicSensor ultrasonic_sensor(ULTRASOUND_SENSOR_PORT);

static Gyroscope gyroscope(GYRO_SENSOR_PORT);

Robot::Robot() {
    _chassis = new Chassis(CHASSIS_ADVANCE_MOTOR_PORT, CHASSIS_STEERING_MOTOR_PORT, GYRO_SENSOR_PORT);
    _arm = new Arm(ARM_MOTOR_PORT, ARM_MOTOR_CLAW_PORT);
    _ultrasonic = new UltrasonicSensor(&ultrasonic_sensor);
    _ultrasonic->set_detection_threshold(20);
    _line_follower_sensor = new LineFollowerSensor(&line_follower);
    _color_sensor = new ColorSensor(&color_sensor);
    
}

Robot::~Robot() {
    delete _arm;
    delete _chassis;
}

Chassis* Robot::chassis() {
    return _chassis;
}

Arm* Robot::arm() {
    return _arm;
}

void Robot::initialize_sensors() {
    _chassis->initialize();
    _color_sensor->initialize();
}

void Robot::do_emergency_stop() {
    do_pause();
    _status = "EMERGENCY STOP";
}

void Robot::do_mechanic_stop() {
    do_emergency_stop();
    _status = "MECHANIC EMERGENCY STOP";
}

void Robot::do_electric_stop() {
    do_emergency_stop();
    _status = "ELECTRIC EMERGENCY STOP";
}

void Robot::do_pause() {
    _chassis->stop_movement();
    _chassis->stop_steering();
    _arm->stop();
    _arm->stop_claw();
}

void Robot::do_resume() {
    _status = "RESUME";
    if (!_is_paused) return;
    _chassis->stop_movement();
    _chassis->stop_steering();
    _arm->stop();
    _arm->stop_claw();
}

void Robot::do_scenario_auto_test() {
    boolean is_object_detected = _ultrasonic->is_object_detected();
    boolean is_line_detected = _line_follower_sensor->is_line_detected();

    _chassis->stop_movement();

    if (!is_line_detected && !is_object_detected) {
        _chassis->forward();
    }

    else if (is_line_detected && is_object_detected) {
        _chassis->stop_movement();
    }

    else if (is_line_detected && !is_object_detected) {
        _chassis->stop_movement();
        delay(500);
        _chassis->backward();
        delay(2000);
    }

    else if (!is_line_detected && is_object_detected) {
        _chassis->stop_movement();
        Serial.println(random(2));
        random(2) == 0 ? _chassis->steer_to_angle(-25) : _chassis->steer_to_angle(25);
        delay(700);
        _chassis->stop_steering();
    }
}

void Robot::do_scenario_try() {
    _arm->close_claw();
    delay(2000);
    _arm->open_claw();
    delay(1000);
}

void Robot::do_scenario_conversion() {
    _chassis->_gyroscope->calibrate();
}

int Robot::update_current_zone() {
    if (_color_sensor->is_in_start_zone()) {
        _current_zone = ZONE_START_CODE;
    }
    else if (_color_sensor->is_in_center_or_twenty_two_zone()) {
    _current_zone = ZONE_CENTER_CODE;
    }
    else if (_color_sensor->is_in_point_zone()) {
        _current_zone = ZONE_POINT_CODE;
    }
    else if (_color_sensor->is_in_bar_zone()) {
        _current_zone = ZONE_BAR_CODE;
    }
    return _current_zone;
}

int Robot::get_current_zone() {
    return _current_zone;
}

int Robot::get_score() {
    return _score;
}

String Robot::get_robot_data() {
    String data = "Score: ";
    data += String(get_score());

    data += "\ncurrent scenario: ";
    data += String(_status);
    data += "\n";

    data += "\nCurrent action: ";
    data += String(_status);
    data += "\n";

    data += "\nCurrent zone: ";
    data += String(_current_zone);
    data += "\nObject detected: ";

    data += "\nBall is held ?: ";
    data += "False";//TODO
    data += "\n";

    data += "\nBall position: ";
    data += "False"; //TODO
    data += "\n";

    // DEBUG 
    data += "\nObject is detected?: ";
    data += String(_ultrasonic->is_object_detected());
    data += "\n";

    data += "\nUltrasonic distance: ";
    data += String(_ultrasonic->get_distance());
    data += "\n";

    data += "Is line detected: ";
    data += String(_line_follower_sensor->is_line_detected());
    data += "\n";

    data += "Angle Z: ";
    data += String(_chassis->_gyroscope->get_angle_z());
    data += " \n";

    data += " \n";

    return data;
}