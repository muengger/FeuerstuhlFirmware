#ifndef OONBOARDLED_H
#define OONBOARDLED_H
#include <arduino.h>
class OnBoardLed{
    public:
    OnBoardLed();
    ~OnBoardLed();

    int SetColor(uint32_t _Color);
    int SetBrightness(int _Brightness);
    int ToggleHeartBeat();
    private:
    int Brightness;
    int Color;

};

#endif //OONBOARDLED_H