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
    int GetBattCharge();
    float GetRPS();
    void SetTorque(float torque);
    void SetMaxSpeed(float Speed);
    float GetMaxSpeed();
    struct sOdriveError{
        uint8_t OdriveError; 
        uint32_t OdriveAxix0Error;
        uint32_t OdriveAxix1Error;
        uint32_t OdriveAxix0MotorError;
        uint32_t OdriveAxix1MotorError;
        uint32_t OdriveControllerError;
        uint32_t OdriveSensorlessEstimatorError;
        uint32_t OdriveEncoderError;
    };
    void ActualizeOdriveError();
    sOdriveError GetOdriveError();
    
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
    sOdriveError OdriveError;

    ConfigData * pConfigData;
    
};

#endif //ODRIVE_H