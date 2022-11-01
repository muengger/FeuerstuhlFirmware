#ifndef BUTTONS_H
#define BUTTONS_H

#include <vector>



class Buttons{
public:
    enum eButtonEvent{  eNoEvent,
                        eButtonUpPressShort,eButtonUpPressLong,
                        eButtonDownPressShort,eButtonDownPressLong,
                        eButtonRightPressShort,eButtonRightPressLong,
                        eButtonLeftPressShort,eButtonLeftPressLong,
                        eButtonMidPressShort,eButtonMidPressLong,
                        eButtonPWRPressShort,eButtonPWRPressLong
                        };
    Buttons();
    ~Buttons();

    int Init();
    //Its important to call this func with 10Hz
    bool ReadCyclic();
    //if you get an event its deleted 
    enum eButtonEvent GetEvent();
private:

    void addEvent(enum eButtonEvent Event);

    int BT_Up_CNT;
    int BT_Down_CNT;
    int BT_Mid_CNT;
    int BT_Right_CNT;
    int BT_Left_CNT;
    int BT_PWR_CNT;
    bool ON_OFF;
    std::vector <enum eButtonEvent> vEvent;

    

};

#endif //BUTTONS_H