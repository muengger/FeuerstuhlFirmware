#include "StateMaschine.h"

StateMaschine::StateMaschine(Odrive * _pOdrive,Trottle * _pTrottle,ConfigData * _pConfigData){
    State = eStop;
    Torque = 0;
    pOdrive = _pOdrive;
    pTrottle = _pTrottle;
    pConfigData = _pConfigData;
    SpeedState = pConfigData->GetDriveParam()->DriveState;
    loBatt = 0;
}

StateMaschine::~StateMaschine(){

}
void StateMaschine::CyclicRun(){
    CheckVoltage();

    switch (State)
    {
    case eStop:
        pOdrive->SetTorque(0);
    break;
    case eRun:
    {
        float MaxTorque = pConfigData->GetDriveParam()->MaxTorquePerState[pConfigData->GetDriveParam()->DriveState];
        int Trottle = pTrottle->GetTrottleVal();
        float torque = (MaxTorque/1000) * ((float)Trottle);
        if(loBatt){
            if(torque > 0.5){
                torque = 0.5;
            }
        }
        pOdrive->SetTorque(torque);
    }
    break;
    case eError:
        pOdrive->SetTorque(0);
    break;
    default:
    break;
    }
}
StateMaschine::eStates StateMaschine::GetRunState(){
    return State;
}

int StateMaschine::SetRunState(eStates NewState){

    if(NewState == eRun){
        if(pTrottle->GetTrottleVal()== 0){ //check if Trottle is 0 
            State = NewState;
            SetSpeedState(pConfigData->GetDriveParam()->DriveState);
            pOdrive->Start();
        }
    }else{
        State = NewState;
        pOdrive->Stop();
    }
    return 0;
}

ConfigData::eSpeedState StateMaschine::GetSpeedState(){
    return SpeedState;
}
void StateMaschine::SetSpeedState(ConfigData::eSpeedState _SpeedState){
    SpeedState =  _SpeedState;
    pOdrive->SetMaxSpeed(pConfigData->GetDriveParam()->MaxSpeedPerState[SpeedState]);
}

void StateMaschine::CheckVoltage(){
     static int counter = 0;
    
    if(pOdrive->GetBusVoltage() < 35){
        counter++;
    }else{
        counter--;
    }
    if(counter < 0){
        counter = 0;
        loBatt = 0;
    }else if (counter > 300){
        counter = 100;
        loBatt = 1;
    }
}
bool StateMaschine::GetLoBatt(){
    return loBatt;
}