#include <Arduino.h>

#include "ODrive/ODrive.h"
#include "Display/Display.h"
#include "Button/Buttons.h"
#include "ConfigData/ConfigData.h"
#include "Trottle/Trottle.h"
#include "OnboardLedRGB/OnBoardLed.h"
#include "Config/PinConfig.h"


Buttons cButtons;
ConfigData cConfigData;
Odrive cOdrive(&cConfigData);
OnBoardLed cOnBoardLed;
Trottle cTrottle(&cConfigData);
StateMaschine cStateMaschine(&cOdrive,&cTrottle,&cConfigData);
Display cDisplay(&cOdrive,&cButtons,&cTrottle,&cConfigData,&cStateMaschine);





void setup() {
  
  //For Debbuging
  
  //while (!Serial); //Whait while Serial is connected in VSC
  
  delay(1000);
  cButtons.Init();
  digitalWrite(PIN_HOLD_PWR,true);
  delay(1000);

  Serial.begin(9600);
  cOdrive.Init();
  cDisplay.Init();
  cTrottle.Init();
  cOnBoardLed.SetColor(0);
  cOnBoardLed.SetBrightness(10);

}

void loop() {
  static unsigned long oldmilisecond100Hz = 0;
  static unsigned long oldmilisecond10Hz = 0;
  static unsigned long oldmilisecond20Hz = 0;
  static unsigned long oldmilisecond1Hz = 0;
  unsigned long newmillisecond = millis();
  static bool buttonPressed;

  if((oldmilisecond100Hz+10) < newmillisecond){ //100Hz
    oldmilisecond100Hz = newmillisecond;
    if(cButtons.ReadCyclic() == true){
      buttonPressed = true;
    }
    
    cOdrive.CyclicUpdate();

  } 
  if((oldmilisecond20Hz+50) < newmillisecond){ //20Hz
    oldmilisecond20Hz = newmillisecond;
    cTrottle.Update();
    cStateMaschine.CyclicRun(buttonPressed); 
    buttonPressed = false;
    
  }
  if((oldmilisecond10Hz+100) < newmillisecond){ //10Hz
    oldmilisecond10Hz = newmillisecond;
    cDisplay.ComputeCyclic();
  } 
  if((oldmilisecond1Hz+1000) < newmillisecond){ //1Hz
    oldmilisecond1Hz = newmillisecond;
    cOnBoardLed.ToggleHeartBeat();
  }  
  
}