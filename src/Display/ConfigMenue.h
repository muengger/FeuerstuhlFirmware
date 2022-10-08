#ifndef CONFIG_MENUE_H
#define CONFIG_MENUE_H
#include <vector>
#include "Display/Screen.h"
#include "Display/ConfigZeile.h"

class ConfigMenue : Screen{
    public:
    ConfigMenue(Display * _pDisplay,Buttons * _pButtons,ConfigData * _pConfigData);
    ~ConfigMenue();
    int CyclicProcess();
    private:
    std::vector<ConfigZeile> vConfigZeile;
    ConfigData * pConfigData;
    int cursor;
    int top;
    int entry;

};

#endif //CONFIG_MENUE_H