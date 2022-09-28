#ifndef HOMESCREEN_H
#define HOMESCREEN_H
#include "Display/Screen.h"

class HomeScreen : Screen{
    public:
    HomeScreen(Display * _pDisplay,Buttons * _pButtons);
    ~HomeScreen();
    int CyclicProcess();
    private:
    int DrawSpeed(float speed);
    int DrawMaxSpeed(float speed);
    int DrawStatic();
    int DrawTrottle(int  trottle);
    int DrawBatt(int  percent);
    int DrawState(int State);

};

#endif //HOMESCREEN_H
