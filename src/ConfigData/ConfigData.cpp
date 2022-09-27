#include "ConfigData/ConfigData.h"
#include <FlashAsEEPROM_SAMD.h>

FlashStorage(DataStorage, ConfigData::AllParam);

ConfigData::ConfigData(){
    DataStorage.read(sAllParam);
    if(sAllParam.Initialized != 0x1234){
        //Set Default Param
        sAllParam.Initialized = 0x1234;
        sAllParam.sTrottleParam.MaxVal = 956;
        sAllParam.sTrottleParam.MinVal = 0;
        sAllParam.sTrottleParam.DeadZone = 10;
        sAllParam.sTrottleParam.Neutral = 339;
        DataStorage.write(sAllParam);
    }

}

ConfigData::~ConfigData(){

}

ConfigData::TrottleParam ConfigData::GetTrottleParam(){
    return sAllParam.sTrottleParam;
}
void ConfigData::SetTrottleParam(struct TrottleParam _Param){
    sAllParam.sTrottleParam = _Param;
    DataStorage.write(sAllParam);
}