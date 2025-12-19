#include "Robot.h"
#include "MeMegaPi.h" // The ONLY file to include this!
#include "Wire.h"
#include "UltrasonicSensor.h"
#include "Ihm.h"

static MeLineFollower line_follower(LINE_FOLLOWER_SENSOR_PORT);
static MeColorSensor color_sensor(COLOR_SENSOR_PORT);
static MeGyro gyro_sensor(GYRO_SENSOR_PORT);
static MeUltrasonicSensor ultrasonic_sensor(ULTRASOUND_SENSOR_PORT);

static Motor motor_arm(ARM_MOTOR_PORT);
static Motor motor_chassis_advance(CHASSIS_FB_MOTOR_PORT);
static Motor motor_chassis_steering(CHASSIS_LR_MOTOR_PORT);
static Motor motor_arm_claw(ARM_MOTOR_CLAW_PORT); // Motor on PORT4B

Robot::Robot() {
    _arm = new Arm(&motor_arm, &motor_arm_claw);
    _chassis = new Chassis(&motor_chassis_advance, &motor_chassis_steering);
    _ultrasonic = new UltrasonicSensor(&ultrasonic_sensor);
    _ultrasonic->set_detection_threshold(20);
    _gyroscope = new Gyroscope(&gyro_sensor);
    _line_follower_sensor = new LineFollowerSensor(&line_follower);
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
    _gyroscope->initialize();

}

void Robot::do_emergency_stop() {
    _chassis->stop_movement();
    _chassis->stop_steering();
    _arm->stop();
    _arm->stop_claw();
}

void Robot::move_arm() {
    switch (_line_follower_sensor->read_sensors()) {
    case S1_IN_S2_IN:
        _arm->_motor_claw->set_analogic_speed(0);
        break;
    case S1_IN_S2_OUT:
        _arm->_motor_claw->set_analogic_speed(255);
        break;
    case S1_OUT_S2_IN:
        _arm->_motor_claw->set_analogic_speed(-255);
        break;
    case S1_OUT_S2_OUT:
        _arm->_motor_claw->set_analogic_speed(0);
        break;
    default:
        _arm->_motor_claw->set_analogic_speed(0);
        break;
    }
}

void Robot::move_left_right_randomly() {


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
        _chassis->backward();
        delay(2000);
    }

    else if (!is_line_detected && is_object_detected) {
        _chassis->stop_movement();
        Serial.println(random(2));
        // random(2) == 0 ? Serial.println("left") : Serial.println("right");
        random(2) == 0 ? _chassis->turn_left() : _chassis->turn_right();
        delay(700);
        _chassis->stop_steering();
    }

}

void Robot::do_scenario_try() {
    _ultrasonic->get_distance();
    _chassis->forward();
}

void Robot::do_scenario_conversion() {

}
