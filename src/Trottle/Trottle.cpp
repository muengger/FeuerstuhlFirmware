#include "Trottle/Trottle.h"
#include "Config/PinConfig.h"
#include "ConfigData/ConfigData.h"
#include <arduino.h>

Trottle::Trottle(ConfigData * _pConfigData){
    pConfigData = _pConfigData;
    LowestValue = 0;
    StopValue = 0;
    StopTollerance = 0;
    HighestValue = 0;

}

Trottle::~Trottle(){}

int Trottle::Init(){
  ConfigData::TrottleParam Param = pConfigData->GetTrottleParam();
    LowestValue = Param.MinVal;
    StopValue = Param.Neutral;
    StopTollerance = Param.DeadZone / 2;
    HighestValue = Param.MaxVal;
    scaleLow = 1000 /((float)StopValue -  (float)StopTollerance - (float)LowestValue);
    offsetHigh = StopValue + StopTollerance;
    scaleHigh = 1000 / ((float)HighestValue - (float)offsetHigh);
    return 0;
}

int Trottle::Update(){
  RawVal = analogRead(PIN_TROTTLE_SENSOR);
  if(RawVal < LowestValue ){
    CurrentSpeedPromille = -1000;
  }else if(RawVal < (StopValue - StopTollerance)){ //Negative Value
    CurrentSpeedPromille = ((RawVal - (StopValue -  StopTollerance) - LowestValue) * scaleLow);
  }else if (RawVal > (StopValue + StopTollerance)){ //Positive Value
    CurrentSpeedPromille = (RawVal - StopValue - StopTollerance) * scaleHigh;     
  }else if (RawVal > HighestValue){
    CurrentSpeedPromille = 1000;
  }else{
    CurrentSpeedPromille = 0;
  }
  if(CurrentSpeedPromille > 1000){
    CurrentSpeedPromille = 1000;
  }else if (CurrentSpeedPromille < -1000){
    CurrentSpeedPromille = -1000;
  }
  return CurrentSpeedPromille;
}

int Trottle::GetTrottleVal(){
    return CurrentSpeedPromille;
}

int Trottle::CalibrateNeutral(){
  static int counter = 0;
  static int Arr[30];
  Arr[counter] = analogRead(PIN_TROTTLE_SENSOR);
  counter++;
  if(counter == 30){
    float res = 0;
    for(int i = 0;i<30;i++){
      res+=Arr[i];
    }
    res = res/30;
    StopValue = res;
    ConfigData::TrottleParam Param = pConfigData->GetTrottleParam();
    Param.Neutral = res;
    pConfigData->SetTrottleParam(Param);
    return 1;
  }
  return 0;
}

int Trottle::CalibrateMinMax(){
  static int counter = 0;
  static int Arr[50];
  Arr[counter] = analogRead(PIN_TROTTLE_SENSOR);
  counter++;
  if(counter == 50){
    int low = 0;
    int high = 0;
    for(int i = 0;i<50;i++){
      if(Arr[i] > high){
        high = Arr[i];
      }
      if(Arr[i] < low){
        low = Arr[i];
      }
    }
    LowestValue = low;
    HighestValue = high;
    ConfigData::TrottleParam Param = pConfigData->GetTrottleParam();
    Param.MaxVal = high;
    Param.MinVal = low;
    pConfigData->SetTrottleParam(Param);
    return 1;
  }
  return 0;
}