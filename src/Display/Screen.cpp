#include "Screen.h"

Screen::Screen(Display * _pDisplay,Buttons * _pButtons){
    pDisplay = _pDisplay;
    pButtons = _pButtons;
    FirstRun = 1;
}
Screen::~Screen(){

}
    
int Screen::CyclicProcess(){
return 0;
}