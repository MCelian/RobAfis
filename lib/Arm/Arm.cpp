#include "Arm.h"

Arm::Arm(Motor* motor) {
    _motor = motor;
}

void Arm::initialize() {
    turnPositive();
};

// void Arm::moveToGrabPosition() {
//     int position = -9999;
//     int noMoveCount = 0;
//     int SAMPLE_MS = 5;
//     int MARGIN_STEER_POSITION = 5;

//     _motor->updateEncoderValue();
//     int lastPos = _motor->getPulsePosition();

//     tempMotorArm = _motor;
//     attachInterrupt(_motor->getInterruptionNumber(), updatePulseCount, RISING);
//     raise();

//     while (noMoveCount < NO_MOVE_THRESHOLD && abs(position - lastPos) >= MARGIN_STEER_POSITION) {
//         _motor->updateEncoderValue();
//         delay(SAMPLE_MS);
//         long pos = _motor->getPulsePosition();
//         int delta = abs(pos - lastPos);

//         if (delta <= MARGIN_STEER_POSITION) {
//             noMoveCount++;
//         } else {
//             noMoveCount = 0;
//             lastPos = pos;
//         }

//         if (_motor->checkAndStopIfBlocked(NO_MOVE_THRESHOLD)) {
//             break;
//         }
//     }
//     _motor->stop();
//     detachInterrupt(_motor->getInterruptionNumber());
//     tempMotorArm = nullptr;
// }
// // void Arm::raise() {
// //     _motor->set_analogic_speed(MAX_SPEED);
// // }

// // void Arm::lower() {
// //     _motor->set_analogic_speed(-MAX_SPEED);
// // }

// // void Arm::stop() {
// //     _motor->set_analogic_speed(0);
// // }

// // void Arm::close_claw() {
// //     _motor_claw->set_analogic_speed(MAX_SPEED);
// // }

// // void Arm::open_claw() {
// //     _motor_claw->set_analogic_speed(-MAX_SPEED);
// // }

// // void Arm::stop_claw() {
// //     _motor_claw->set_analogic_speed(0);
// // }
