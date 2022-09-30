#ifndef ODRIVE_H
#define ODRIVE_H
#include <Arduino.h>
#include <ODriveArduino.h>
#include "wiring_private.h" // pinPeripheral() function



class Odrive{
    public:
    Odrive(void);
    ~Odrive();

    int Init();
    int CyclicUpdate();
    int Start();
    int Stop();
    float GetBusVoltage();
    float GetRPM();

    private:
    //Odrive Configuration
    Uart *ODriveSerial;// (&sercom3, 0, 1, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ODriveArduino * odrive;//(ODriveSerial);
    float BusVoltage;
    float RPM_L;
    float RPM_R;
    int Run_Stop;
};

#endif //ODRIVE_H