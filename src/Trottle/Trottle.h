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
    int CalibrateNeutral(int * Neutral);
    int CalibrateMinMax(int * Max,int *Min);
    int ActCalibration(int Max,int Min,int Neutral);
    int SafeCalibration();
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