#include <Arduino.h>

#include "ODrive/ODrive.h"
#include "Display/Display.h"
#include "Button/Buttons.h"
#include "ConfigData/ConfigData.h"
#include "Trottle/Trottle.h"

Odrive cOdrive;
Buttons cButtons;
ConfigData cConfigData;
Trottle cTrottle;
Display cDisplay;




void setup() {
  cOdrive.Init();
  cButtons.Init();
  
  
  //Init Trottle with parameters
  ConfigData::TrottleParam sTrottleParam = cConfigData.GetTrottleParam();
  cTrottle.Init(sTrottleParam.MinVal,sTrottleParam.Neutral,sTrottleParam.DeadZone,sTrottleParam.MaxVal);
  cDisplay.Init();

}

void loop() {
  static unsigned long milisecond = 0;
  if(milisecond < (millis()+10)){
    milisecond = millis();
    cButtons.ReadCyclic();
    cTrottle.Update();
  } 
}