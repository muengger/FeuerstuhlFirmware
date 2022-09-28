#ifndef STATEMASCHINE_H
#define STATEMASCHINE_H
#include <Arduino.h>
#include "ODrive/ODrive.h"

class StateMaschine{
    public:
    enum eStates{eStop,eRun,eError};
    StateMaschine(Odrive * _pOdrive);
    ~StateMaschine();

    eStates GetState();
    int SetState(eStates NewState);
    private:
    eStates State;
    float Torque;
    Odrive * pOdrive;
};

#endif //STATEMASCHINE_H