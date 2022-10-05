#ifndef STATEMASCHINE_H
#define STATEMASCHINE_H
#include <Arduino.h>
#include "ODrive/ODrive.h"
#include "Trottle/Trottle.h"


class StateMaschine{
    public:
    enum eStates{eStop,eRun,eError};
    StateMaschine(Odrive * _pOdrive,Trottle * _pTrottle);
    ~StateMaschine();
    void CyclicRun();
    eStates GetState();
    int SetState(eStates NewState);
    private:
    eStates State;
    float Torque;
    Odrive * pOdrive;
    Trottle * pTrottle;
};

#endif //STATEMASCHINE_H