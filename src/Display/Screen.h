#ifndef SCREEN_H
#define SCREEN_H
#include "Display.h"
#include "Button/Buttons.h"

class Display;

class Screen{
public:
    Screen(Display * _pDisplay,Buttons * _pButtons);
    ~Screen();
    virtual int CyclicProcess();
protected:
    Display * pDisplay;
    Buttons * pButtons;

    int FirstRun;
};

#endif //SCREEN_H