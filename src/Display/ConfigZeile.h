#ifndef CONFIG_ZEILE_H
#define CONFIG_ZEILE_H

#include "ConfigData/ConfigData.h"
#include "Button/Buttons.h"
#include "Display/Display.h"
#include "Trottle/Trottle.h"
#include "Arduino.h"

class ConfigZeile{
public:
    //Constructor for int variables
    ConfigZeile(String _Desc,int * _pIData,int _IMax,int _IMin,String _Unit);
    //Constructor for float variables
    ConfigZeile(String _Desc,float * _pFData,float _FMax,float _FMin,int _Decimal,String _Unit);
    //Constructor for eSpeed State
    ConfigZeile(String _Desc,ConfigData::eSpeedState * _pEData);
    //Constructor for Sensor Calibration
    ConfigZeile(String _Desc,int * _CaliMax,int * _CaliMin,int * _Neutral,Trottle * _pTrottle);

    ~ConfigZeile();

    int DrawZeile(Buttons::eButtonEvent Event,Display * pDisplay);
    String * pGetDescription();


private:
    enum eDataType{eInt,eFloat,eSpeedState,eSensorCal};
    eDataType Type;
    String Desc;
    String * pSData;
    int * pIData;
    float * pFData;
    float FMax;
    float FMin;
    int Decimal;
    ConfigData::eSpeedState * pEData;
    String Unit;
    int * CaliMax;
    int * CaliMin;
    int * Neutral;
    Trottle * pTrottle;

};

#endif //CONFIG_ZEILE_H