#ifndef CONFIG_MENUE_H
#define CONFIG_MENUE_H

#include "Display/Screen.h"
#include "Display/ConfigZeile.h"

class ConfigMenue : Screen{
    public:
    ConfigMenue(Display * _pDisplay,Buttons * _pButtons);
    ~ConfigMenue();
    int CyclicProcess();
    private:


};

#endif //CONFIG_MENUE_H