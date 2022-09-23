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

    private:
    //Odrive Configuration
    Uart *ODriveSerial;// (&sercom3, 0, 1, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ODriveArduino * odrive;//(ODriveSerial);
};

#endif //ODRIVE_H