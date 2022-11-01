#ifndef HOMESCREEN_H
#define HOMESCREEN_H
#include "Display/Screen.h"

class HomeScreen : Screen{
    public:
    HomeScreen(Display * _pDisplay,Buttons * _pButtons,ConfigData * _pConfigData);
    ~HomeScreen();
    int CyclicProcess();
    private:
    int DrawSpeed(float speed);
    int DrawMaxSpeed(float speed);
    int DrawStatic();
    int DrawTrottle(int  trottle);
    int DrawBatt(int  percent,bool LoBatt);
    int DrawState(int State);
    int DrawSpeedState(ConfigData::eSpeedState SpeedState);

};

#endif //HOMESCREEN_H
