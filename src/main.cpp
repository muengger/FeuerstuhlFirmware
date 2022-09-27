#include <Arduino.h>

#include "ODrive/ODrive.h"
#include "Display/Display.h"
#include "Button/Buttons.h"
#include "ConfigData/ConfigData.h"
#include "Trottle/Trottle.h"
#include "OnboardLedRGB/OnBoardLed.h"

Odrive cOdrive;
Buttons cButtons;
ConfigData cConfigData;
OnBoardLed cOnBoardLed;
Trottle cTrottle(&cConfigData);
Display cDisplay(&cOdrive,&cButtons);




void setup() {
  //For Debbuging
  Serial.begin(9600);
  while (!Serial); //Whait while Serial is connected in VSC




  cOdrive.Init();
  cButtons.Init();
  cDisplay.Init();
  cTrottle.Init();
  cOnBoardLed.SetColor(0);
  cOnBoardLed.SetBrightness(10);

}

void loop() {
  static unsigned long oldmilisecond100Hz = 0;
  static unsigned long oldmilisecond10Hz = 0;
  static unsigned long oldmilisecond1Hz = 0;
  unsigned long newmillisecond = millis();
  if((oldmilisecond100Hz+10) < newmillisecond){ //100Hz
    oldmilisecond100Hz = newmillisecond;
    cButtons.ReadCyclic();
  } 

  if((oldmilisecond10Hz+100) < newmillisecond){ //10Hz
    oldmilisecond10Hz = newmillisecond;
    
    
    cTrottle.Update();
  } 

  if((oldmilisecond1Hz+1000) < newmillisecond){ //1Hz
    oldmilisecond1Hz = newmillisecond;

    cOnBoardLed.ToggleHeartBeat();
  }  
  
}