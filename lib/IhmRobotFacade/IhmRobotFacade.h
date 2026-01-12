#ifndef IHMROBOTFACADE_H
#define IHMROBOTFACADE_H

#include "Ihm.h"
#include "Robot.h"

class IhmRobotFacade {
public:
    IhmRobotFacade(Ihm* ihm, Robot* robot) : _ihm(ihm), _robot(robot) {};
    void executeIhmCommand(int command);
    void sendRobotDataToIhm();
private:
    Ihm* _ihm = nullptr;
    Robot* _robot = nullptr;
};

#endif