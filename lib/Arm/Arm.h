#ifndef ARM_H
#define ARM_H

class Arm {
public:
    Arm(int port) { _port = port; }
private:
    int _port;
};

#endif