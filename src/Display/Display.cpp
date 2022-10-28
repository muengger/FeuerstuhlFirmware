#include "Display.h"
#include <Wire.h>
#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <splash.h>

#include "HomeScreen.h"
#include "ConfigMenue.h"




    Display::Display(Odrive * _pOdrive,Buttons * _pButtons,Trottle * _pTrottle,ConfigData * _pConfigData,StateMaschine * _pStateMaschine){
        pOdrive = _pOdrive;
        pButtons = _pButtons;
        pTrottle = _pTrottle;
        pConfigData = _pConfigData;
        pStateMaschine = _pStateMaschine;
    }
    Display::~Display(){}
    int Display::Init(){
        display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
        display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
        display->display();
        display->clearDisplay();
        display->setTextSize(1);      // Normal 1:1 pixel scale
        display->setTextColor(SSD1306_WHITE); // Draw white text
        display->setCursor(0, 0);     // Start at top-left corner
        display->cp437(true);         // Use full 256 char 'Code Page 437' font
        display->print("High\nin the Roller Chair\nTurbo Controller");
        display->display();

        //Init All the screens
        pScreenArr[0] = (Screen *) new HomeScreen(this,pButtons,pConfigData);
        pScreenArr[1] = (Screen *) new ConfigMenue(this,pButtons,pConfigData,pTrottle,pOdrive);

        return 0;
    }
Adafruit_SSD1306 * Display::GetRealDisplay(){
    return display;
}
Trottle * Display::GetTrottle(){
    return pTrottle;
}
void Display::ComputeCyclic(){
    pScreenArr[ActualShownScreen]->CyclicProcess();
}
float Display::GetVoltage(){
    return pOdrive->GetBusVoltage();
}
float Display::GetSpeed(){
    return pConfigData->RPSToSpeed(pOdrive->GetRPS());
}
StateMaschine::eStates Display::GetRunState(){
    return pStateMaschine->GetRunState();
}
void Display::SetRunState(StateMaschine::eStates NewState){
    pStateMaschine->SetRunState(NewState);
}
void Display::SetScreenToMenue(){
    ActualShownScreen = 1;
}
void Display::SetScreenToHome(){
    ActualShownScreen = 0;
}