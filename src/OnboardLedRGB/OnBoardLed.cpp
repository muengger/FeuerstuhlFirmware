#include "OnBoardLed.h"
#include <Adafruit_DotStar.h>
#define NUMPIXELS 1 // Number of LEDs in strip

// Here's how to control the LEDs from any two pins:
#define DATAPIN    8
#define CLOCKPIN   6
Adafruit_DotStar Led(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

    OnBoardLed::OnBoardLed(){
        Led.begin();
        Led.setPixelColor(0,0);
        Led.setBrightness(80);
        Led.show();  // Turn all LEDs off ASAP
    }
    OnBoardLed::~OnBoardLed(){

    }

    int OnBoardLed::SetColor(uint32_t _Color){
        Led.setPixelColor(0,_Color);
        return 0;
    }
    int OnBoardLed::SetBrightness(int _Brightness){
        Led.setBrightness(_Brightness);
        Led.show();
        return 0;
    }
    int OnBoardLed::ToggleHeartBeat(){
        static int state = 0;
        if(state == 0){
            state = 1;
            Led.setPixelColor(0,0x00FF0000);
        }else if(state == 1){
            state = 2;
            Led.setPixelColor(0,0x0000FF00);            
        }else{
            state = 0;
            Led.setPixelColor(0,0x000000FF);     
        }
        Led.show();
        return 0;
    }
    