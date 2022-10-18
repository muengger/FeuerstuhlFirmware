#ifndef CONFIG_MENUE_H
#define CONFIG_MENUE_H
#include <vector>
#include "Display/Screen.h"
#include "Display/ConfigZeile.h"

class ConfigMenue : Screen{
    public:
    ConfigMenue(Display * _pDisplay,Buttons * _pButtons,ConfigData * _pConfigData,Trottle * _pTrottle);
    ~ConfigMenue();
    int CyclicProcess();
    private:
    std::vector<ConfigZeile> vConfigZeile;
    int cursor;
    int top;
    int entry;
    Trottle * pTrottle;

};

#endif //CONFIG_MENUE_H