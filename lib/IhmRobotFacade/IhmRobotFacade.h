#ifndef IHM_ROBOT_FACADE_H
#define IHM_ROBOT_FACADE_H

#include "Ihm.h"
#include "Robot.h"

class IhmRobotFacade {
public:
    IhmRobotFacade(Ihm* ihm, Robot* robot) : _ihm(ihm), _robot(robot) {};
    
    void executeIhmCommand(char command);
    
    void sendRobotDataToIhm();

    void test() {
        _robot->pivotLookLeft();
        _robot->advanceForwardUntilObstacle();
        _robot->steerCenter();
        _robot->advanceBackwardDuringMs(3000);
    }
private:
    Ihm* _ihm = nullptr;
    Robot* _robot = nullptr;
};

#endif