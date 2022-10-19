#ifndef ODRIVE_H
#define ODRIVE_H
#include <Arduino.h>
#include "wiring_private.h" // pinPeripheral() function
#include "ConfigData/ConfigData.h"



class Odrive{
    public:
    Odrive(ConfigData * _pConfigData);
    ~Odrive();

    int Init();
    int CyclicUpdate();
    int Start();
    int Stop();
    float GetBusVoltage();
    float GetRPS();
    void SetTorque(float torque);
    void SetMaxSpeed(float Speed);
    float GetMaxSpeed();

    private:
    //Odrive Configuration
    Uart *ODriveSerial;// (&sercom3, 0, 1, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    float BusVoltage;
    float MaxRPS;
    bool MaxSpeedUpdate;
    float RPS_L;
    float RPS_R;
    int Run_Stop;
    float Torque_L;
    float Torque_R;
    bool ReadError;
    uint8_t OdriveError; 
    uint32_t OdriveAxix0Error;
    uint32_t OdriveAxix1Error;

    ConfigData * pConfigData;
};

#endif //ODRIVE_H