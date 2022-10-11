#include "ConfigZeile.h"
#include "Arduino.h"
   
    ConfigZeile::ConfigZeile(String _Desc,int * _pIData,int _IMax,int _IMin,int _IStep){
        Type= eInt;
        Desc = _Desc;
        pIData = _pIData;
        IMax = _IMax;
        IMin = _IMin;
        IStep = _IStep;
    }
    ConfigZeile::ConfigZeile(String _Desc,float * _pFData,float _FMax,float _FMin,float _FStep){
        Type= eFloat;
        Desc = _Desc;
        pFData = _pFData;
        FMax = _FMax;
        FMin = _FMin;
        FStep = _FStep;
    }
    ConfigZeile::ConfigZeile(String _Desc,ConfigData::eSpeedState * _pEData){
        Type= eSpeedState;
        Desc = _Desc;
        pEData = _pEData;      
    }
    ConfigZeile::~ConfigZeile(){

    }

    int ConfigZeile::DrawZeile(Buttons::eButtonEvent Event,Display * pDisplay){
        static bool init = true;
        static int ActInt = 0;
        static float ActFloat = 0;
        static int cursor = 0;
        static int Length = 0;
        ConfigData::eSpeedState ActSpeedState = ConfigData::eSpeedState::eChild;

        if(Event == Buttons::eButtonEvent::eButtonLeftPressLong){
            init = true;
            return -1;
        }
        switch(Type)
        {
        case eInt:
            {
                if(init){
                    init = false;
                    ActInt = *pIData;
                }
                pDisplay->GetRealDisplay()->clearDisplay();
                pDisplay->GetRealDisplay()->setTextSize(1);
                pDisplay->GetRealDisplay()->setTextColor(SSD1306_WHITE); 
                pDisplay->GetRealDisplay()->cp437(true); 
                pDisplay->GetRealDisplay()->setCursor(1, 1);
                pDisplay->GetRealDisplay()->print(Desc);
                pDisplay->GetRealDisplay()->setCursor(30, 10);
                String temp(ActInt);
                pDisplay->GetRealDisplay()->print(temp);
                pDisplay->GetRealDisplay()->display();
            }
        break;
        case eFloat:
            {
                if(init){
                    init = false;
                    ActFloat = *pFData; 
                }
                String temp(ActFloat,2);
                Length = temp.length()-1;
                if(Event == Buttons::eButtonEvent::eButtonLeftPressShort){
                    if(cursor < Length){
                        cursor ++;
                        if(cursor == 2){
                            cursor = 3;
                        }
                    }
                }else if(Event == Buttons::eButtonEvent::eButtonRightPressShort){
                    if(cursor > 0){
                        cursor--;
                    }
                    if(cursor == 2){
                        cursor = 1;
                    }
                    
                }else if(Event == Buttons::eButtonEvent::eButtonUpPressShort){
                    
                }else if(Event == Buttons::eButtonEvent::eButtonDownPressShort){
                    
                }
                pDisplay->GetRealDisplay()->clearDisplay();
                pDisplay->GetRealDisplay()->setTextSize(1);
                pDisplay->GetRealDisplay()->setTextColor(SSD1306_WHITE); 
                pDisplay->GetRealDisplay()->cp437(true); 
                pDisplay->GetRealDisplay()->setCursor(1, 1);
                pDisplay->GetRealDisplay()->print(Desc);
                pDisplay->GetRealDisplay()->setCursor(40, 10);

                pDisplay->GetRealDisplay()->drawChar(34+((temp.length()-cursor)*6),20,0x1E,SSD1306_WHITE,0,1);
                pDisplay->GetRealDisplay()->print(temp);
                pDisplay->GetRealDisplay()->display();
            }
        break;
        case eSpeedState:
            {
                if(init){
                    init = false;
                    ActSpeedState = *pEData;
                }
                pDisplay->GetRealDisplay()->clearDisplay();
                pDisplay->GetRealDisplay()->setTextSize(1);
                pDisplay->GetRealDisplay()->setTextColor(SSD1306_WHITE); 
                pDisplay->GetRealDisplay()->cp437(true); 
                pDisplay->GetRealDisplay()->setCursor(1, 1);
                pDisplay->GetRealDisplay()->print(Desc);
                pDisplay->GetRealDisplay()->setCursor(30, 10);
                switch (ActSpeedState)
                {
                case ConfigData::eChild:
                    pDisplay->GetRealDisplay()->print("Child");
                break;
                case ConfigData::eTeeny:
                    pDisplay->GetRealDisplay()->print("Teeny");
                break;
                case ConfigData::eAdult:
                    pDisplay->GetRealDisplay()->print("Adult");
                break;
                case ConfigData::eCracy:
                    pDisplay->GetRealDisplay()->print("Cracy");
                break;   
                case ConfigData::eMaxState:
                    pDisplay->GetRealDisplay()->print("Error");
                break;              
                }
                pDisplay->GetRealDisplay()->display();
            }
        break;
        }
        return 0;
    }

    String * ConfigZeile::pGetDescription(){
        return &Desc;
    }