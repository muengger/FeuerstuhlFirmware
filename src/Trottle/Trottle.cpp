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
    LowestValue = pConfigData->GetTrottleParam()->MinVal;
    StopValue = pConfigData->GetTrottleParam()->Neutral;
    StopTollerance = pConfigData->GetTrottleParam()->DeadZone / 2;
    HighestValue = pConfigData->GetTrottleParam()->MaxVal;
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

int Trottle::CalibrateNeutral(int * Neutral){

  * Neutral = analogRead(PIN_TROTTLE_SENSOR);
  return 0;
}

int Trottle::CalibrateMinMax(int * Max,int *Min){

  int ActVal = analogRead(PIN_TROTTLE_SENSOR);
  if(ActVal < *Min){
    *Min = ActVal;
  }else if (ActVal > *Max){
    *Max = ActVal;
  }
  return 0;
}
int Trottle::ActCalibration(int Max,int Min,int Neutral){
  LowestValue = Min;
  StopValue = Neutral;
  StopTollerance = pConfigData->GetTrottleParam()->DeadZone / 2;
  HighestValue = Max;
  scaleLow = 1000 /((float)StopValue -  (float)StopTollerance - (float)LowestValue);
  offsetHigh = StopValue + StopTollerance;
  scaleHigh = 1000 / ((float)HighestValue - (float)offsetHigh);

  return 0;
}
int Trottle::SafeCalibration(){
  pConfigData->GetTrottleParam()->MinVal = LowestValue;
  pConfigData->GetTrottleParam()->MaxVal = HighestValue;
  pConfigData->GetTrottleParam()->Neutral = StopValue;
  pConfigData->SafeParam();
  return 0;
}