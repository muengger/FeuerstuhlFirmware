#ifndef STATEMASCHINE_H
#define STATEMASCHINE_H
#include <Arduino.h>
#include "ODrive/ODrive.h"
#include "Trottle/Trottle.h"
#include "ConfigData/ConfigData.h"


class StateMaschine{
    public:
    enum eStates{eStop,eRun,eError};
    StateMaschine(Odrive * _pOdrive,Trottle * _pTrottle,ConfigData * _pConfigData);
    ~StateMaschine();
    void CyclicRun();
    eStates GetRunState();
    int SetRunState(eStates NewState);
    ConfigData::eSpeedState GetSpeedState();
    void SetSpeedState(ConfigData::eSpeedState _SpeedState);
    private:
    eStates State;
    ConfigData::eSpeedState SpeedState;
    float Torque;
    Odrive * pOdrive;
    Trottle * pTrottle;
    ConfigData * pConfigData;
};

#endif //STATEMASCHINE_H