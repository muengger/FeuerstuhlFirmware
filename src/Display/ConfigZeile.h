#ifndef CONFIG_ZEILE_H
#define CONFIG_ZEILE_H

#include "ConfigData/ConfigData.h"
#include "Button/Buttons.h"
#include "Display/Display.h"
#include "Arduino.h"

class ConfigZeile{
public:
    
    ConfigZeile(String _Desc,int * _pIData,int _IMax,int _IMin);
    ConfigZeile(String _Desc,float * _pFData,float _FMax,float _FMin,int _Decimal);
    ConfigZeile(String _Desc,ConfigData::eSpeedState * _pEData);
    ~ConfigZeile();

    int DrawZeile(Buttons::eButtonEvent Event,Display * pDisplay);
    String * pGetDescription();


private:
enum eDataType{eInt,eFloat,eSpeedState};
eDataType Type;
String Desc;
String * pSData;
int * pIData;
int IMax;
int IMin;
float * pFData;
float FMax;
float FMin;
int Decimal;
ConfigData::eSpeedState * pEData;

};

#endif //CONFIG_ZEILE_H