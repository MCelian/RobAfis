#include "RobotFactory.h"
#include "MeMegaPi.h"

#define PORT_MOTOR_ADVANCE PORT_1
#define PORT_MOTOR_STEERING PORT_2
#define PORT_MOTOR_ARM PORT_3
#define PORT_MOTOR_CLAW PORT_4

#define PORT_ULTRASONIC_SENSOR PORT_6
#define PORT_LINE_FOLLOWER_SENSOR PORT_7
        
Robot* RobotFactory::createRugbyRobot() {
    RobotBuilder builder;
    RobotDirector director(&builder);

    director.buildFullRugbyRobot(PORT_MOTOR_ADVANCE, PORT_MOTOR_STEERING, PORT_ULTRASONIC_SENSOR, PORT_LINE_FOLLOWER_SENSOR);

    return builder.getResult();
}