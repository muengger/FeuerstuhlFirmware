
#include <Arduino.h>
#include "Button/Buttons.h"
#include "Config/PinConfig.h"
#include "Config/GlobalConfig.h"

#define LONG_PRESS_TIME 100

Buttons::Buttons(){
  BT_Up_CNT = 0;
  BT_Down_CNT = 0;
  BT_Mid_CNT = 0;
  BT_Right_CNT = 0;
  BT_Left_CNT = 0;
  BT_PWR_CNT = 0;
}

Buttons::~Buttons(){
  vEvent.clear();
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
  ON_OFF = true;
  return 0;
}

bool Buttons::ReadCyclic(){
  bool buttonpressed = false;
  if(digitalRead(PIN_BUTTON_UP) == 0){
    BT_Up_CNT++;
    if(BT_Up_CNT == LONG_PRESS_TIME){
      //Serial.print("Button Event := eButtonUpPressLong");
      addEvent(eButtonUpPressLong);
      buttonpressed = true;
    }
  }else{
    if((BT_Up_CNT > 1) && (BT_Up_CNT< LONG_PRESS_TIME)){
      //Serial.print("Button Event := eButtonUpPressShort");
      addEvent(eButtonUpPressShort);
      buttonpressed = true;
    }
    BT_Up_CNT = 0;
  }

  if(digitalRead(PIN_BUTTON_DOWN)== 0){
    BT_Down_CNT++;
    if(BT_Down_CNT == LONG_PRESS_TIME){
      //Serial.print("Button Event := eButtonDownPressLong");
      addEvent(eButtonDownPressLong);
      buttonpressed = true;
    }
  }else{
    if((BT_Down_CNT > 1) && (BT_Down_CNT< LONG_PRESS_TIME)){
      //Serial.print("Button Event := eButtonDownPressShort");
      addEvent(eButtonDownPressShort);
      buttonpressed = true;
    }
    BT_Down_CNT = 0;
  }

  if(digitalRead(PIN_BUTTON_MID)==0){
    BT_Mid_CNT++;
    if(BT_Mid_CNT == LONG_PRESS_TIME){
      //Serial.print("Button Event := eButtonMidPressLong");
      addEvent(eButtonMidPressLong);
      buttonpressed = true;
    }
  }else{
    if((BT_Mid_CNT > 1) && (BT_Mid_CNT< LONG_PRESS_TIME)){
      //Serial.print("Button Event := eButtonMidPressShort");
      addEvent(eButtonMidPressShort);
      buttonpressed = true;
    }
    BT_Mid_CNT = 0;
  }

  if(digitalRead(PIN_BUTTON_RIGHT)==0){
    BT_Right_CNT++;
    if(BT_Right_CNT == LONG_PRESS_TIME){
      //Serial.print("Button Event := eButtonRightPressLong");
      addEvent(eButtonRightPressLong);
      buttonpressed = true;
    }
  }else{
    if((BT_Right_CNT > 1) && (BT_Right_CNT< LONG_PRESS_TIME)){
      //Serial.print("Button Event := eButtonRightPressShort");
      addEvent(eButtonRightPressShort);
      buttonpressed = true;
    }
    BT_Right_CNT = 0;
  }

  if(digitalRead(PIN_BUTTON_LEFT)==0){
    BT_Left_CNT++;
    if(BT_Left_CNT == LONG_PRESS_TIME){
      //Serial.print("Button Event := eButtonLeftPressLong");
      addEvent(eButtonLeftPressLong);
      buttonpressed = true;
    }
  }else{
    if((BT_Left_CNT > 1) && (BT_Left_CNT< LONG_PRESS_TIME)){
      //Serial.print("Button Event := eButtonLeftPressShort");
      addEvent(eButtonLeftPressShort);
      buttonpressed = true;
    }
    BT_Left_CNT = 0;
  }

  if(digitalRead(PIN_BUTTON_ON_OFF)){
    BT_PWR_CNT++;
    if(BT_PWR_CNT == LONG_PRESS_TIME){
      Serial.print("Button Event := eButtonPWRPressLong");
      addEvent(eButtonPWRPressLong);
      buttonpressed = true;
      if(ON_OFF){
        ON_OFF = false;
        digitalWrite(PIN_HOLD_PWR,false);
        while(1);
      }
      

    }
  }else{
    if((BT_PWR_CNT > 1) && (BT_PWR_CNT< LONG_PRESS_TIME)){
      Serial.print("Button Event := eButtonPWRPressShort");
      addEvent(eButtonPWRPressShort);
      buttonpressed = true;
    }
    BT_PWR_CNT = 0;
  }
  return buttonpressed;
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

void Buttons::addEvent(enum eButtonEvent Event){
  if(vEvent.size() < 10){
    vEvent.push_back(Event);
  }else{
    Serial.print("Button Event overflow");
  }
}