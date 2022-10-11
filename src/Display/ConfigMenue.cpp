    #include "ConfigMenue.h"
    ConfigMenue::ConfigMenue(Display * _pDisplay,Buttons * _pButtons,ConfigData * _pConfigData):Screen(_pDisplay,_pButtons){
        pConfigData = _pConfigData;
        vConfigZeile.push_back(ConfigZeile("Speed State",&pConfigData->GetDriveParam()->DriveState));
        vConfigZeile.push_back(ConfigZeile("Trottle Dead Zone",&pConfigData->GetTrottleParam()->DeadZone,30,5,1));
        vConfigZeile.push_back(ConfigZeile("Speed Child Mode",&pConfigData->GetDriveParam()->MaxSpeedPerState[ConfigData::eChild],30,3,1));
        vConfigZeile.push_back(ConfigZeile("Speed Teeny Mode",&pConfigData->GetDriveParam()->MaxSpeedPerState[ConfigData::eTeeny],30,3,1));
        vConfigZeile.push_back(ConfigZeile("Speed Adult Mode",&pConfigData->GetDriveParam()->MaxSpeedPerState[ConfigData::eAdult],30,3,1));
        vConfigZeile.push_back(ConfigZeile("Speed Crazy Mode",&pConfigData->GetDriveParam()->MaxSpeedPerState[ConfigData::eCracy],30,3,1));
        vConfigZeile.push_back(ConfigZeile("Torque Child Mode",&pConfigData->GetDriveParam()->MaxTorquePerState[ConfigData::eChild],6,0.5,0.25));
        vConfigZeile.push_back(ConfigZeile("Torque Teeny Mode",&pConfigData->GetDriveParam()->MaxTorquePerState[ConfigData::eTeeny],6,0.5,0.25));
        vConfigZeile.push_back(ConfigZeile("Torque Adult Mode",&pConfigData->GetDriveParam()->MaxTorquePerState[ConfigData::eAdult],6,0.5,0.25));
        vConfigZeile.push_back(ConfigZeile("Torque Crazy Mode",&pConfigData->GetDriveParam()->MaxTorquePerState[ConfigData::eCracy],6,3.5,0.25));
        vConfigZeile.push_back(ConfigZeile("Wheel Diameter (m)",&pConfigData->GetMotorParam()->WheelDiameter,1,0.005,0.001));
        entry = vConfigZeile.size();
        cursor = 0;
        top = 0;
    }
    ConfigMenue::~ConfigMenue(){

    }
    int ConfigMenue::CyclicProcess(){
        static bool inZeile= false;
        Buttons::eButtonEvent Event = pButtons->GetEvent();
        if(inZeile){
            if(vConfigZeile[cursor].DrawZeile(Event,pDisplay)==0){
                return 0;
            }else{
                inZeile = false;
                return 0;
            }
            
        }
        if(Event == Buttons::eButtonEvent::eButtonDownPressShort){
            if(cursor+1 < entry){
                cursor++;
            }
        }
        else if(Event == Buttons::eButtonEvent::eButtonUpPressShort){
            if(cursor > 0){
                cursor--;
            }
        }
        else if(Event == Buttons::eButtonEvent::eButtonLeftPressLong){
            pDisplay->SetScreenToHome();
        }else if((Event == Buttons::eButtonEvent::eButtonRightPressShort)||(Event == Buttons::eButtonEvent::eButtonMidPressShort)){
            inZeile = true;
            return 0;
        }

        if(cursor > top+5){
            top++;
        }else if(cursor < top){
            top--;
        }
        pDisplay->GetRealDisplay()->clearDisplay();
        pDisplay->GetRealDisplay()->setTextSize(1);
        pDisplay->GetRealDisplay()->setTextColor(SSD1306_WHITE); 
        pDisplay->GetRealDisplay()->cp437(true); 
        for(int i = 0;i<6;i++){
            if(i + top < entry){
                String ZeilenText = *vConfigZeile[i + top].pGetDescription();
                pDisplay->GetRealDisplay()->setCursor(1, (i* 10)+2);
                if(i+top == cursor){
                    pDisplay->GetRealDisplay()->print(">" + ZeilenText);
                }else{
                    pDisplay->GetRealDisplay()->print(" " + ZeilenText);
                }
                
            }
        }
        pDisplay->GetRealDisplay()->display();
        return 0;
    }
 
    //vector<ConfigZeile> vConfigZeile;