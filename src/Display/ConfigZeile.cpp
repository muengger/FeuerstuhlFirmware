#include "ConfigZeile.h"
#include "Arduino.h"
   
   
   
   
    ConfigZeile::ConfigZeile(String _Desc,String * _pSData){
        Type= eString;
        Desc = _Desc;
        pSData = _pSData;
    }
    ConfigZeile::ConfigZeile(String _Desc,int * _pIData,int _IMax,int _IMin,int _IStep){
        Type= eInt;
        Desc = _Desc;
        pIData = _pIData;
        IMax = _IMax;
        IMin = _IMin;
        IStep = _IStep;
    }
    ConfigZeile::ConfigZeile(String _Desc,float * _pFData,float _FMax,float _FMin,float _FStep){
        Type= eFloat;
        Desc = _Desc;
        pFData = _pFData;
        FMax = _FMax;
        FMin = _FMin;
        FStep = _FStep;
    }
    ConfigZeile::ConfigZeile(String _Desc,ConfigData::eSpeedState * _pEData){
        Type= eSpeedState;
        Desc = _Desc;
        pEData = _pEData;      
    }
    ConfigZeile::~ConfigZeile(){

    }

    void ConfigZeile::DrawZeile(){

    }

    String * ConfigZeile::pGetDescription(){
        return &Desc;
    }