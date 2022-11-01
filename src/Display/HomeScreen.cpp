#include "HomeScreen.h"
   
   
   
    HomeScreen::HomeScreen(Display * _pDisplay,Buttons * _pButtons,ConfigData * _pConfigData):Screen(_pDisplay,_pButtons,_pConfigData){

    }
    HomeScreen::~HomeScreen(){

    }

    int HomeScreen::CyclicProcess(){
        static float test = 0;
        static int test2= 0;
        static float MaxSpeed = 0;
        Buttons::eButtonEvent Event = pButtons->GetEvent();
        StateMaschine::eStates RunState =  pDisplay->GetRunState();
        ConfigData::eSpeedState SpeedState = pConfigData->GetDriveParam()->DriveState;
        if(Event == Buttons::eButtonEvent::eButtonMidPressLong){
            Serial.println("ChangeToMenue");
            pDisplay->SetScreenToMenue();
            pDisplay->SetRunState(StateMaschine::eStates::eStop);
        }else if (Event == Buttons::eButtonEvent::eButtonUpPressLong){
            if(RunState == StateMaschine::eStates::eStop){
                pDisplay->SetRunState(StateMaschine::eStates::eRun);
            }else{
                pDisplay->SetRunState(StateMaschine::eStates::eStop);
            }
        }
        //float Voltage = pDisplay->GetVoltage();
        int BattChage = pDisplay->GetBattCharge();
        float Speed = pDisplay->GetSpeed();
        
        if(MaxSpeed < Speed){
            MaxSpeed = Speed;
        }
        if(FirstRun ){
            FirstRun = 0;
        }
        pDisplay->GetRealDisplay()->clearDisplay();
        DrawStatic();
        DrawSpeed(Speed);
        DrawMaxSpeed(MaxSpeed);
        DrawTrottle(pDisplay->GetTrottle()->GetTrottleVal());
        DrawBatt(BattChage);
        DrawState((int)RunState);
        DrawSpeedState(SpeedState);
        test= test +0.1;
        test2++;
        if(test > 30){
            test = 0;
        }
        if(test2 > 100){
            test2 = 0;
        }
        pDisplay->GetRealDisplay()->display();

        
        
        return 0;
    }

    int HomeScreen::DrawSpeed(float speed){
        int mitteX = 32;
        int mitteY = 32; 
        double winkel = (225 - (speed * 9))*PI/180;
        int x = (int)(cos(winkel) * 15);
        int y = ((int)(sin(winkel) * 15))*(-1);
        pDisplay->GetRealDisplay()->drawLine(mitteX,mitteY,mitteX+x,mitteY+y,SSD1306_WHITE);
        return 0;
    }

    int HomeScreen::DrawMaxSpeed(float speed){
        int mitteX = 32;
        int mitteY = 32; 
        double winkel = (225 - (speed * 9))*PI/180;
        int x1 = (int)(cos(winkel) * 28);
        int y1 = ((int)(sin(winkel) * 28))*(-1);
        int x2 = (int)(cos(winkel) * 33);
        int y2 = ((int)(sin(winkel) * 33))*(-1);
        pDisplay->GetRealDisplay()->drawLine(mitteX+x1,mitteY+y1,mitteX+x2,mitteY+y2,SSD1306_WHITE);
        return 0;
    }

    int HomeScreen::DrawTrottle(int  trottle){
        int middle = 26;
        int max = 12;

        int Y = (-trottle / (1000/max)) + middle;
        pDisplay->GetRealDisplay()->drawLine(72,Y,77,Y,SSD1306_WHITE);
        return 0;
    }  

    int HomeScreen::DrawBatt(int  percent){
        
        float max = 13;
        float min = 41;
        int Y = ((min - max)/100) * (100 - percent) + max;
        int h = min - Y;
        pDisplay->GetRealDisplay()->fillRoundRect(87,Y,6,h,2,SSD1306_WHITE);
        return 0;
    } 

    int HomeScreen::DrawState(int State){
        pDisplay->GetRealDisplay()->setCursor(62, 56);
        switch(State){
            case 0:
                pDisplay->GetRealDisplay()->print("State:Stop");
            break;
            case 1:
                pDisplay->GetRealDisplay()->print("State:Run");
            break;
            case 2:
                pDisplay->GetRealDisplay()->print("State:Error");
            break;
            default:
                pDisplay->GetRealDisplay()->print("State:Error");
        }

        return 0;
    }
    int HomeScreen::DrawSpeedState(ConfigData::eSpeedState SpeedState){
        pDisplay->GetRealDisplay()->setCursor(62, 46);
        //pDisplay->GetRealDisplay()->setTextColor(SSD1306_WHITE); 
        switch (SpeedState)
        {
            case ConfigData::eSpeedState::eChild:
                pDisplay->GetRealDisplay()->print("Speed:Child");
            break;
            case ConfigData::eSpeedState::eTeeny:
                pDisplay->GetRealDisplay()->print("Speed:Teeny");
            break;
            case ConfigData::eSpeedState::eAdult:
                pDisplay->GetRealDisplay()->print("Speed:Adult");
            break;      
            case ConfigData::eSpeedState::eCracy:
                pDisplay->GetRealDisplay()->print("Speed:Cracy");
            break;
            case ConfigData::eSpeedState::eMaxState:
                pDisplay->GetRealDisplay()->print("Speed:Error");
            break;
        }
        
        return 0;
    }
    int HomeScreen::DrawStatic(){
        pDisplay->GetRealDisplay()->drawCircle(32,32,30,SSD1306_WHITE);
        pDisplay->GetRealDisplay()->fillCircle(32,32,3,SSD1306_WHITE);
        
        pDisplay->GetRealDisplay()->drawLine(2,32,4,32,SSD1306_WHITE);
        pDisplay->GetRealDisplay()->drawLine(60,32,62,32,SSD1306_WHITE);
        pDisplay->GetRealDisplay()->drawLine(32,2,32,4,SSD1306_WHITE);
        pDisplay->GetRealDisplay()->drawLine(11,11,13,13,SSD1306_WHITE);
        pDisplay->GetRealDisplay()->drawLine(53,11,51,13,SSD1306_WHITE);
        pDisplay->GetRealDisplay()->drawLine(53,53,51,51,SSD1306_WHITE);
        pDisplay->GetRealDisplay()->drawLine(11,53,13,51,SSD1306_WHITE);

        pDisplay->GetRealDisplay()->drawChar(13,43,'0',SSD1306_WHITE,SSD1306_WHITE,1);

        pDisplay->GetRealDisplay()->drawChar(7,29,'5',SSD1306_WHITE,SSD1306_WHITE,1);

        pDisplay->GetRealDisplay()->drawChar(13,15,'1',SSD1306_WHITE,SSD1306_WHITE,1);
        pDisplay->GetRealDisplay()->drawChar(17,15,'0',SSD1306_WHITE,SSD1306_WHITE,1);

        pDisplay->GetRealDisplay()->drawChar(27,8,'1',SSD1306_WHITE,SSD1306_WHITE,1);
        pDisplay->GetRealDisplay()->drawChar(31,8,'5',SSD1306_WHITE,SSD1306_WHITE,1);

        pDisplay->GetRealDisplay()->drawChar(43,15,'2',SSD1306_WHITE,SSD1306_WHITE,1);
        pDisplay->GetRealDisplay()->drawChar(49,15,'0',SSD1306_WHITE,SSD1306_WHITE,1);

        pDisplay->GetRealDisplay()->drawChar(47,29,'2',SSD1306_WHITE,SSD1306_WHITE,1);
        pDisplay->GetRealDisplay()->drawChar(53,29,'5',SSD1306_WHITE,SSD1306_WHITE,1);

        pDisplay->GetRealDisplay()->drawChar(43,43,'3',SSD1306_WHITE,SSD1306_WHITE,1);
        pDisplay->GetRealDisplay()->drawChar(49,43,'0',SSD1306_WHITE,SSD1306_WHITE,1);

        pDisplay->GetRealDisplay()->drawRoundRect(70,10,10,34,4,SSD1306_WHITE);

        pDisplay->GetRealDisplay()->drawRoundRect(85,10,10,34,4,SSD1306_WHITE);
        pDisplay->GetRealDisplay()->fillRect(17,55,32,10,SSD1306_WHITE);
        pDisplay->GetRealDisplay()->fillRect(60,45,68,20,SSD1306_WHITE);


        pDisplay->GetRealDisplay()->setTextSize(1);
        pDisplay->GetRealDisplay()->setTextColor(SSD1306_WHITE); 
        pDisplay->GetRealDisplay()->setCursor(62, 1);
        pDisplay->GetRealDisplay()->cp437(true); 
        pDisplay->GetRealDisplay()->print("PWR Batt");
        pDisplay->GetRealDisplay()->setCursor(100, 12);   
        pDisplay->GetRealDisplay()->print("Full");
        pDisplay->GetRealDisplay()->setCursor(100, 34);   
        pDisplay->GetRealDisplay()->print("Low");
        pDisplay->GetRealDisplay()->setCursor(62, 56);    
        pDisplay->GetRealDisplay()->print("State: ");
        pDisplay->GetRealDisplay()->setTextColor(SSD1306_BLACK); 
        pDisplay->GetRealDisplay()->setCursor(18, 56);   
        pDisplay->GetRealDisplay()->print("Speed");
        return 0;
    }