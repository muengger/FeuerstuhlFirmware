#ifndef TROTTLE_H
#define TROTTLE_H

#include "ConfigData/ConfigData.h"

class Trottle{
    public:
    Trottle(ConfigData * _pConfigData);
    ~Trottle();

    int Init();
    int Update();
    int GetTrottleVal();
    //Call These function with 10Hz until 1 is returned the its finished
    int CalibrateNeutral();
    //Call These function with 10Hz until 1 is returned the its finished
    int CalibrateMinMax();
    private:
    int LowestValue;
    int StopValue;
    int StopTollerance;
    int HighestValue;
    int RawVal;
    int LasRawVal;
    int CurrentSpeedPromille;
    float scaleLow;
    float scaleHigh;
    int offsetHigh;
    ConfigData * pConfigData;
};

#endif //TROTTLE_H