#include "StateMaschine.h"

StateMaschine::StateMaschine(Odrive * _pOdrive){
    State = eStop;
    Torque = 0;
    pOdrive = _pOdrive;
}

StateMaschine::~StateMaschine(){

}

StateMaschine::eStates StateMaschine::GetState(){
    return State;
}

int StateMaschine::SetState(eStates NewState){
    State = NewState;
    return 0;
}