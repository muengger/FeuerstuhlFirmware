#include "StateMaschine.h"
#include "Config/PinConfig.h"

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
void StateMaschine::CyclicRun(bool ButtonPressed){
    CheckVoltage();
    int Trottle = pTrottle->GetTrottleVal();
    SwitchOFFTimer(Trottle,ButtonPressed);

    switch (State)
    {
    case eStop:
        pOdrive->SetTorque(0);
    break;
    case eRun:
    {
        float MaxTorque = pConfigData->GetDriveParam()->MaxTorquePerState[pConfigData->GetDriveParam()->DriveState];
        
        float torque = (MaxTorque/1000) * ((float)Trottle);
        if(loBatt){
            if(torque > 0){
                torque = 0;
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
    static int counterLo = 0;
    static int counterEmpty = 0;
    
    if(pOdrive->GetBusVoltage() < 35){
        counterLo++;
    }else{
        counterLo--;
    }
    if(pOdrive->GetBusVoltage() < 33){
        counterEmpty++;
    }else{
        counterEmpty--;
    }

    if(counterLo < 0){
        counterLo = 0;
        loBatt = 0;
    }else if (counterLo > 100){
        counterLo = 100;
        loBatt = 1;
    }

    if(counterEmpty < 0){
        counterEmpty = 0;

    }else if (counterEmpty > 200){
        digitalWrite(PIN_HOLD_PWR,false);
        while(1);
    }
}
bool StateMaschine::GetLoBatt(){
    return loBatt;
}

void StateMaschine::SwitchOFFTimer(int Trottle,bool buttonpressed){
    static int counter = 0;
    if(counter > 6000){
        digitalWrite(PIN_HOLD_PWR,false);
        while(1);
    }
    if((Trottle != 0)||(buttonpressed)){
        counter = 0;
    }
    counter++;
}