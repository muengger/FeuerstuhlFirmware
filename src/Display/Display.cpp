#include "Display/Display.h"
#include <Wire.h>
#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <splash.h>



    Display::Display(Odrive * _Odrive,Buttons _Buttons){
        pOdrive = _Odrive;
        pButtons = _Buttons;
    }
    Display::~Display(){}
    int Display::Init(){
        display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
        display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
        display->display();
        display->clearDisplay();
        display->setTextSize(1);      // Normal 1:1 pixel scale
        display->setTextColor(SSD1306_WHITE); // Draw white text
        display->setCursor(0, 0);     // Start at top-left corner
        display->cp437(true);         // Use full 256 char 'Code Page 437' font
        display->print("High\nin the Roller Chair\nTurbo Controller");
        display->display();
        return 0;
    }

void Display::ComputeCyclic(){
    
}