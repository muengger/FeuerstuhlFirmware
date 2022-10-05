#include "StateMaschine.h"

StateMaschine::StateMaschine(Odrive * _pOdrive,Trottle * _pTrottle){
    State = eStop;
    Torque = 0;
    pOdrive = _pOdrive;
    pTrottle = _pTrottle;
}

StateMaschine::~StateMaschine(){

}
void StateMaschine::CyclicRun(){
    switch (State)
    {
    case eStop:
    pOdrive->SetTorque(0);
    break;
    case eRun:
    pTrottle->GetTrottleVal();
    pOdrive->SetTorque(0);
    break;
    case eError:

    break;
    default:
    break;
    }
}
StateMaschine::eStates StateMaschine::GetState(){
    return State;
}

int StateMaschine::SetState(eStates NewState){
    State = NewState;
    return 0;
}