#include "Trottle/Trottle.h"
#include "Config/PinConfig.h"
#include <arduino.h>

Trottle::Trottle(){
    LowestValue = 0;
    StopValue = 0;
    StopTollerance = 0;
    HighestValue = 0;
    LastBackwardValue = 0;
    LastForwardValue = 0;
    lastInputValue = 0;
}

Trottle::~Trottle(){}

int Trottle::Init(int _minValue, int _stopValue, int _stopTollerance, int _maxValue){
    LowestValue = _minValue;
    StopValue = _stopValue;
    StopTollerance = _stopTollerance;
    HighestValue = _maxValue;

    LastBackwardValue = StopValue-(StopTollerance/2);
    LastForwardValue = StopValue+(StopTollerance/2);

    lastInputValue = 0;
    return 0;
}

int Trottle::Update(){
    RawVal = analogRead(PIN_TROTTLE_SENSOR);
      if(RawVal == lastInputValue) {
    // nothing to do
  } else {
    // calculateNewValues
    if(RawVal <= LastBackwardValue) { // direction: backward
      if(RawVal < LowestValue) RawVal = LowestValue;
      CurrentSpeedPromille = (LastBackwardValue-LowestValue-(RawVal-LowestValue)+1)*1000/(double)(LastBackwardValue-LowestValue+1);
      isForwardFlag = false;
    } else {
      if(RawVal >= LastForwardValue) { // direction: forward
        if(RawVal > HighestValue) RawVal = HighestValue;
        CurrentSpeedPromille = (RawVal-LastForwardValue+1)*1000/(double)(HighestValue-LastForwardValue+1);
        isForwardFlag = true;
      } else { // should be StopValue or within tollerance

      }
    }
    lastInputValue = RawVal;
  }
  return CurrentSpeedPromille;
}

int Trottle::GetTrottleVal(){
    return CurrentSpeedPromille;
}
