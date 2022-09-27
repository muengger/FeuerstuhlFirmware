#ifndef DISPLAY_H
#define DISPLAY_H


#include <Adafruit_SSD1306.h>
#include "Button/Buttons.h"
#include "ODrive/ODrive.h"

//Display config
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

class Display{
    public:
    Display(Odrive * _Odrive,Buttons * _Buttons);
    ~Display();

    int Init();
    void ComputeCyclic();
    private:
    Odrive * pOdrive;
    Buttons * pButtons;
    Adafruit_SSD1306 * display;//(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

};

#endif //DISPLAY_H