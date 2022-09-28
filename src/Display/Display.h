#ifndef DISPLAY_H
#define DISPLAY_H


#include <Adafruit_SSD1306.h>
#include "Button/Buttons.h"
#include "ODrive/ODrive.h"
#include "Trottle/Trottle.h"
class Screen;
#include "Screen.h"

//Display config
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

class Display{
    public:
    Display(Odrive * _pOdrive,Buttons * _pButtons,Trottle * _pTrottle);
    ~Display();

    int Init();
    void ComputeCyclic();
    Adafruit_SSD1306 * GetRealDisplay();
    Trottle * GetTrottle();
    private:
    Odrive * pOdrive;
    Buttons * pButtons;
    Trottle * pTrottle;
    Adafruit_SSD1306 * display;//(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    int ActualShownScreen;
    Screen * pScreenArr[10];

};

#endif //DISPLAY_H