
#include <Arduino.h>
#include "Button/Buttons.h"
#include "Config/PinConfig.h"

#define LONG_PRESS_TIME 10

Buttons::Buttons(){

}

Buttons::~Buttons(){

}


int Buttons::Init(){
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_HOLD_PWR,OUTPUT);
  pinMode(PIN_BUTTON_ON_OFF,INPUT);
  pinMode(PIN_BUTTON_UP,INPUT_PULLUP);
  pinMode(PIN_BUTTON_DOWN,INPUT_PULLUP);
  pinMode(PIN_BUTTON_RIGHT,INPUT_PULLUP);
  pinMode(PIN_BUTTON_LEFT,INPUT_PULLUP);
  pinMode(PIN_BUTTON_MID,INPUT_PULLUP);
  return 0;
}

void Buttons::ReadCyclic(){
  if(digitalRead(PIN_BUTTON_UP)){
    BT_Up_CNT++;
    if(BT_Up_CNT == LONG_PRESS_TIME){
      vEvent.push_back(eButtonUpPressLong);
    }
  }else{
    if((BT_Up_CNT > 1) && (BT_Up_CNT< LONG_PRESS_TIME)){
      if(BT_Up_CNT< LONG_PRESS_TIME){
        vEvent.push_back(eButtonUpPressShort);
      }
      BT_Up_CNT = 0;
    }
  }

  if(digitalRead(PIN_BUTTON_DOWN)){
    BT_Down_CNT++;
    if(BT_Down_CNT == LONG_PRESS_TIME){
      vEvent.push_back(eButtonDownPressLong);
    }
  }else{
    if((BT_Down_CNT > 1) && (BT_Down_CNT< LONG_PRESS_TIME)){
      if(BT_Down_CNT< LONG_PRESS_TIME){
        vEvent.push_back(eButtonDownPressShort);
      }
      BT_Down_CNT = 0;
    }
  }

  if(digitalRead(PIN_BUTTON_MID)){
    BT_Mid_CNT++;
    if(BT_Mid_CNT == LONG_PRESS_TIME){
      vEvent.push_back(eButtonMidPressLong);
    }
  }else{
    if((BT_Mid_CNT > 1) && (BT_Mid_CNT< LONG_PRESS_TIME)){
      if(BT_Mid_CNT< LONG_PRESS_TIME){
        vEvent.push_back(eButtonMidPressShort);
      }
      BT_Mid_CNT = 0;
    }
  }

  if(digitalRead(PIN_BUTTON_RIGHT)){
    BT_Right_CNT++;
    if(BT_Right_CNT == LONG_PRESS_TIME){
      vEvent.push_back(eButtonRightPressLong);
    }
  }else{
    if((BT_Right_CNT > 1) && (BT_Right_CNT< LONG_PRESS_TIME)){
      if(BT_Right_CNT< LONG_PRESS_TIME){
        vEvent.push_back(eButtonRightPressShort);
      }
      BT_Right_CNT = 0;
    }
  }

  if(digitalRead(PIN_BUTTON_LEFT)){
    BT_Left_CNT++;
    if(BT_Left_CNT == LONG_PRESS_TIME){
      vEvent.push_back(eButtonLeftPressLong);
    }
  }else{
    if((BT_Left_CNT > 1) && (BT_Left_CNT< LONG_PRESS_TIME)){
      if(BT_Left_CNT< LONG_PRESS_TIME){
        vEvent.push_back(eButtonLeftPressShort);
      }
      BT_Left_CNT = 0;
    }
  }

  if(digitalRead(PIN_BUTTON_ON_OFF)){
    BT_PWR_CNT++;
    if(BT_PWR_CNT == LONG_PRESS_TIME){
      vEvent.push_back(eButtonPWRPressLong);
    }
  }else{
    if((BT_PWR_CNT > 1) && (BT_PWR_CNT< LONG_PRESS_TIME)){
      if(BT_PWR_CNT< LONG_PRESS_TIME){
        vEvent.push_back(eButtonPWRPressShort);
      }
      BT_PWR_CNT = 0;
    }
  }
}
//if you get an event its deleted 
Buttons::eButtonEvent Buttons::GetEvent(){
  if(vEvent.empty()){
    return eNoEvent;
  }else{
    eButtonEvent event = vEvent[0];
    vEvent.erase (vEvent.begin());
    return event;
  }
}