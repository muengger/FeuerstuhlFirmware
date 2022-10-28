#include "ConfigData/ConfigData.h"
#include <FlashAsEEPROM_SAMD.h>

FlashStorage(DataStorage, ConfigData::AllParam);

ConfigData::ConfigData(){
    DataStorage.read(sAllParam);
    if(sAllParam.Initialized != 0x1234){
        //Set Default Param
        sAllParam.Initialized = 0x1234;
        sAllParam.sTrottleParam.MaxVal = 958;
        sAllParam.sTrottleParam.MinVal = 3;
        sAllParam.sTrottleParam.DeadZone = 10;
        sAllParam.sTrottleParam.Neutral = 341;
        sAllParam.sDriveParam.DriveState = eChild;
        sAllParam.sDriveParam.MaxSpeedPerState[eChild]= 10;
        sAllParam.sDriveParam.MaxSpeedPerState[eTeeny]= 20;
        sAllParam.sDriveParam.MaxSpeedPerState[eAdult]= 30;
        sAllParam.sDriveParam.MaxSpeedPerState[eCracy]= 40;
        sAllParam.sDriveParam.MaxTorquePerState[eChild]= 1;
        sAllParam.sDriveParam.MaxTorquePerState[eTeeny]= 2;
        sAllParam.sDriveParam.MaxTorquePerState[eAdult]= 3;
        sAllParam.sDriveParam.MaxTorquePerState[eCracy]= 4;
        sAllParam.sMotorParam.WheelDiameter = 0.16;
        
        DataStorage.write(sAllParam);
    }

}

ConfigData::~ConfigData(){

}

ConfigData::TrottleParam * ConfigData::GetTrottleParam(){
    return &sAllParam.sTrottleParam;
}
void ConfigData::SafeParam(){
    DataStorage.write(sAllParam);
}


ConfigData::MotorParam * ConfigData::GetMotorParam(){
    return &sAllParam.sMotorParam;
}
ConfigData::DriveParam * ConfigData::GetDriveParam(){
    return &sAllParam.sDriveParam;
}
float ConfigData::RPSToSpeed(float RPS){
    float diam = sAllParam.sMotorParam.WheelDiameter;
    float speed = RPS * diam * PI * 3.6;
    return speed;
}
float ConfigData::SpeedToRPS(float Speed){
    float diam = sAllParam.sMotorParam.WheelDiameter;
    float RPS = Speed/(diam * PI * 3.6);
    return RPS;
}