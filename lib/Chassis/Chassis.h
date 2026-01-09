#ifndef CHASSIS_H
#define CHASSIS_H

#include "Motor.h"
#define FIND_PWM 100
#define SAMPLE_MS 100
#define NO_MOVE_THRESHOLD 5
#define MARGIN_STEER_POSITION 5
#define GEAR_MULTIPLIER 72.0f / 8.0f

#define ADVANCE_SPEED 200

class Chassis {
public:
    Chassis(int portAdvance, int portSteering);
    void findSteeringLimits();
    void steerLeft();
    void steerRight();
    void steerCenter();
    void advanceForward();
    void advanceBackward();
    void advanceStop();

    int getSteerLeftLimit() const { return _steerLeftLimit; }
    void setSteerLeftLimit(int steerLeftLimit) { _steerLeftLimit = steerLeftLimit; }

    int getSteerRightLimit() const { return _steerRightLimit; }
    void setSteerRightLimit(int steerRightLimit) { _steerRightLimit = steerRightLimit; }

    int getCenterPosition() const { return _centerPosition; }
    void setCenterPosition(int centerPosition) { _centerPosition = centerPosition; }

    int getCenterWheelDeg() const { return _centerWheelDeg; }
    void setCenterWheelDeg(int centerWheelDeg) { _centerWheelDeg = centerWheelDeg; }

    int getCurrentRaw() const { return _currentRaw; }
    void setCurrentRaw(int currentRaw) { _currentRaw = currentRaw; }

    int getCurrentWheelDeg() const { return _currentWheelDeg; }
    void setCurrentWheelDeg(int currentWheelDeg) { _currentWheelDeg = currentWheelDeg; }

    int getCurrentPosition() const { return _currentPostion; }
    void setCurrentPosition(int currentPostion) { _currentPostion = currentPostion; }

    void waitAndKeepAlive(unsigned long ms);

    void steerUntilStop(int pwmSign);

    void steerToPosition(int position);
    
private:
    Motor* _motorAdvance;
    Motor* _motorSteering;
    int _steerLeftLimit;
    int _steerRightLimit;
    int _centerWheelDeg = 0;
    int _currentRaw = 0;
    int _currentWheelDeg = 0;
    int _currentPostion = 0;
    int _centerPosition = 0;
};

#endif
