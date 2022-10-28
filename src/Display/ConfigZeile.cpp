#include "ConfigZeile.h"
#include "Arduino.h"
   
    ConfigZeile::ConfigZeile(String _Desc,int * _pIData,int _IMax,int _IMin,String _Unit){
        Type= eInt;
        Desc = _Desc;
        pIData = _pIData;
        FMax = (float)_IMax;
        FMin = (float)_IMin;
        Decimal = 0;
        Unit = _Unit;
    }
    ConfigZeile::ConfigZeile(String _Desc,float * _pFData,float _FMax,float _FMin,int _Decimal,String _Unit){
        Type= eFloat;
        Desc = _Desc;
        pFData = _pFData;
        FMax = _FMax;
        FMin = _FMin;
        Decimal = _Decimal;
        Unit = _Unit;
    }
    ConfigZeile::ConfigZeile(String _Desc,ConfigData::eSpeedState * _pEData){
        Type= eSpeedState;
        Desc = _Desc;
        pEData = _pEData;      
    }
    ConfigZeile::ConfigZeile(String _Desc,int * _CaliMax,int * _CaliMin,int * _Neutral,Trottle * _pTrottle){
        Type= eSensorCal;
        Desc = _Desc;
        CaliMax = _CaliMax;
        CaliMin = _CaliMin;
        Neutral = _Neutral;
        pTrottle = _pTrottle;
     
    }   
    ConfigZeile::ConfigZeile(String _Desc,Odrive * _pOdrive){
        Type= eODrive;
        Desc = _Desc; 
        pOdrive = _pOdrive;
    }
    ConfigZeile::~ConfigZeile(){

    }

    int ConfigZeile::DrawZeile(Buttons::eButtonEvent Event,Display * pDisplay){
        static bool init = true;
        static float ActFloat = 0;
        static int cursor = 0;
        static int Length = 0;
        static ConfigData::eSpeedState ActSpeedState = ConfigData::eSpeedState::eChild;

        if(Event == Buttons::eButtonEvent::eButtonLeftPressLong){
            init = true;
            return -1;
        }
        if(Type == eInt || Type == eFloat){
                if(init){
                    init = false;
                    if(Type == eInt ){
                        ActFloat = (float)*pIData;
                    }else{
                        ActFloat = *pFData; 
                    }
                    

                }
                String temp(ActFloat,Decimal);
                if(Decimal > 0){
                    Length = temp.length()-1;
                }else{
                    Length = temp.length()-1;
                }
                
                if(Event == Buttons::eButtonEvent::eButtonLeftPressShort){
                    if(cursor < Length){
                        cursor ++;
                        if(Decimal > 0){
                            if(cursor == Decimal){
                                cursor = Decimal+1;
                            }   
                        }

                    }
                }else if(Event == Buttons::eButtonEvent::eButtonRightPressShort){
                    if(cursor > 0){
                        cursor--;
                    }
                    if(Decimal > 0){
                        if(cursor == Decimal){
                            cursor = Decimal-1;
                        }   
                    }
                    
                }else if(Event == Buttons::eButtonEvent::eButtonUpPressShort){
                    float temp = ActFloat;
                    if(Decimal == 0){
                        temp += pow(10,(cursor - Decimal));
                    }else if(Decimal > cursor){
                        temp += pow(10,(cursor - Decimal));
                    }else{
                       temp += pow(10,(cursor - Decimal -1)); 
                    }
                    if((temp <= FMax)&&(temp >= FMin)){
                        ActFloat = temp;
                    }                
                    
                }else if(Event == Buttons::eButtonEvent::eButtonDownPressShort){
                    float temp = ActFloat;
                    if(Decimal == 0){
                        temp -= pow(10,(cursor - Decimal));
                    }else if(Decimal > cursor){
                        temp -= pow(10,(cursor - Decimal));
                    }else{
                       temp -= pow(10,(cursor - Decimal -1)); 
                    }    
                    if((temp <= FMax)&&(temp >= FMin)){
                        ActFloat = temp;
                    }                
                }else if(Event == Buttons::eButtonEvent::eButtonMidPressLong){
                    init = true;
                    if(Type == eInt){
                        *pIData= (int)ActFloat;
                    }else{
                        *pFData= ActFloat;
                    }
                    return 1;
                }              
                pDisplay->GetRealDisplay()->clearDisplay();
                pDisplay->GetRealDisplay()->setTextSize(1);
                pDisplay->GetRealDisplay()->setTextColor(SSD1306_WHITE); 
                pDisplay->GetRealDisplay()->cp437(true); 
                pDisplay->GetRealDisplay()->setCursor(5, 1);
                pDisplay->GetRealDisplay()->print(Desc);
                pDisplay->GetRealDisplay()->setCursor(40, 20);

                pDisplay->GetRealDisplay()->drawChar(34+((temp.length()-cursor)*6),30,0x1E,SSD1306_WHITE,0,1);

                pDisplay->GetRealDisplay()->print(temp + " " + Unit);
                pDisplay->GetRealDisplay()->setCursor(2, 50);
                pDisplay->GetRealDisplay()->print("<-Long:=Back, O:=Safe");
                pDisplay->GetRealDisplay()->display();
        }else if(Type == eSpeedState){
                if(init){
                    init = false;
                    ActSpeedState = *pEData;
                }
                if(Event == Buttons::eButtonEvent::eButtonUpPressShort){
                    if(ActSpeedState < ConfigData::eCracy){
                        ActSpeedState = (ConfigData::eSpeedState)(((int)ActSpeedState) + 1);
                    }
                    
                }else if(Event == Buttons::eButtonEvent::eButtonDownPressShort){
                    if(ActSpeedState > 0){
                        ActSpeedState = (ConfigData::eSpeedState)(((int)ActSpeedState) - 1);
                    }         
                }else if(Event == Buttons::eButtonEvent::eButtonMidPressLong){
                    init = true;
                    *pEData = ActSpeedState;
                    return 1;
                }              
                pDisplay->GetRealDisplay()->clearDisplay();
                pDisplay->GetRealDisplay()->setTextSize(1);
                pDisplay->GetRealDisplay()->setTextColor(SSD1306_WHITE); 
                pDisplay->GetRealDisplay()->cp437(true); 
                pDisplay->GetRealDisplay()->setCursor(1, 1);
                pDisplay->GetRealDisplay()->print(Desc);
                pDisplay->GetRealDisplay()->setCursor(40, 20);
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
                pDisplay->GetRealDisplay()->setCursor(2, 50);
                pDisplay->GetRealDisplay()->print("<-Long:=Back, O:=Safe");
                pDisplay->GetRealDisplay()->display();
        }else if(Type == eSensorCal){
                static int state = 0;
                static int  Max,Min,Neutral; 
                if(init){
                    state = 0;
                    Max = 50;
                    Min = 100;
                    Neutral = 200;
                    init = false;
                }
                if(Event == Buttons::eButtonEvent::eButtonUpPressShort){
                    
                }else if(Event == Buttons::eButtonEvent::eButtonDownPressShort){
        
                }else if(Event == Buttons::eButtonEvent::eButtonMidPressLong){
                    init = true;
                    return 1;
                }else if(Event == Buttons::eButtonEvent::eButtonMidPressShort){
                    state++;
                }  
                if(state == 0){  
                      
                    pTrottle->CalibrateMinMax(&Max,&Min);
                    pDisplay->GetRealDisplay()->clearDisplay();
                    pDisplay->GetRealDisplay()->setTextSize(1);
                    pDisplay->GetRealDisplay()->setTextColor(SSD1306_WHITE); 
                    pDisplay->GetRealDisplay()->cp437(true); 
                    pDisplay->GetRealDisplay()->setCursor(1, 1);
                    pDisplay->GetRealDisplay()->print(Desc);
                    pDisplay->GetRealDisplay()->setCursor(1, 15);
                    pDisplay->GetRealDisplay()->print("Move trigger on all sides if values does not change anymore    press short middle ");
                    String sMax(Max);
                    String sMin(Min);
                    pDisplay->GetRealDisplay()->setCursor(1, 50);
                    pDisplay->GetRealDisplay()->print("Max:"+sMax+"Min:"+sMin);
                    pDisplay->GetRealDisplay()->display();
                }else if(state == 1){
                    pTrottle->CalibrateNeutral(&Neutral);
                    pDisplay->GetRealDisplay()->clearDisplay();
                    pDisplay->GetRealDisplay()->setTextSize(1);
                    pDisplay->GetRealDisplay()->setTextColor(SSD1306_WHITE); 
                    pDisplay->GetRealDisplay()->cp437(true); 
                    pDisplay->GetRealDisplay()->setCursor(1, 1);
                    pDisplay->GetRealDisplay()->print(Desc);
                    pDisplay->GetRealDisplay()->setCursor(1, 15);
                    pDisplay->GetRealDisplay()->print("Leave Trigger in Neutral if values does not change anymore    press short middle ");
                    String sMax(Max);
                    String sMin(Min);
                    String sNeutral(Neutral);
                    pDisplay->GetRealDisplay()->setCursor(1, 50);
                    pDisplay->GetRealDisplay()->print("Max:"+sMax+" Min:"+sMin+"Neutral:"+sNeutral);
                    pDisplay->GetRealDisplay()->display();
                }else if(state == 2){
                    pTrottle->ActCalibration(Max,Min,Neutral);
                    pTrottle->SafeCalibration();
                    init = true;
                    return 1;
                }
        }else if (Type == eODrive){
                if(init){
                    init = false;
                    pOdrive->ActualizeOdriveError();
                }
                if(Event == Buttons::eButtonEvent::eButtonMidPressShort){
                    pOdrive->ActualizeOdriveError();
                } 
                pDisplay->GetRealDisplay()->clearDisplay();
                pDisplay->GetRealDisplay()->setTextSize(1);
                pDisplay->GetRealDisplay()->setTextColor(SSD1306_WHITE); 
                pDisplay->GetRealDisplay()->cp437(true); 
                pDisplay->GetRealDisplay()->setCursor(1, 1);
                pDisplay->GetRealDisplay()->print(Desc);
                pDisplay->GetRealDisplay()->setCursor(1, 15);
                pDisplay->GetRealDisplay()->print("Odrive Error ");

                pDisplay->GetRealDisplay()->display();
        }
    
        return 0;
    }

    String * ConfigZeile::pGetDescription(){
        return &Desc;
    }