#ifndef ODRIVE_H
#define ODRIVE_H
#include <Arduino.h>
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
    float GetRPS();
    void SetTorque(float torque);

    private:
    //Odrive Configuration
    Uart *ODriveSerial;// (&sercom3, 0, 1, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    float BusVoltage;
    float RPS_L;
    float RPS_R;
    int Run_Stop;
    float Torque_L;
    float Torque_R;
};

#endif //ODRIVE_H