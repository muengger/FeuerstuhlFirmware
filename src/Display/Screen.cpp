#include "Screen.h"

Screen::Screen(Display * _pDisplay,Buttons * _pButtons,ConfigData * _pConfigData){
    pDisplay = _pDisplay;
    pButtons = _pButtons;
    pConfigData = _pConfigData;
    FirstRun = 1;
}
Screen::~Screen(){

}
    
int Screen::CyclicProcess(){
return 0;
}