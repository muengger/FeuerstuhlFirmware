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
    void ReadCyclic();
    //if you get an event its deleted 
    enum eButtonEvent GetEvent();
    private:
    bool BT_Up;
    int BT_Up_CNT;
    bool BT_Down;
    int BT_Down_CNT;
    bool BT_Mid;
    int BT_Mid_CNT;
    bool BT_Right;
    int BT_Right_CNT;
    bool BT_Left;
    int BT_Left_CNT;
    bool BT_PWR;
    int BT_PWR_CNT;
    std::vector <enum eButtonEvent> vEvent;
    

};

#endif //BUTTONS_H