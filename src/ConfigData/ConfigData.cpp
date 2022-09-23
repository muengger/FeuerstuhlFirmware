#include "ConfigData/ConfigData.h"
#include <FlashAsEEPROM_SAMD.h>

FlashStorage(DataStorage, ConfigData::AllParam);

ConfigData::ConfigData(){
    DataStorage.read(sAllParam);
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