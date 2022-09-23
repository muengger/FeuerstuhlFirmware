#include "ODrive.h"

Odrive::Odrive(void){

}
Odrive::~Odrive(){

}

int Odrive::Init(){

    ODriveSerial = new Uart(&sercom3, 0, 1, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    odrive = new ODriveArduino(*ODriveSerial);
    ODriveSerial->begin(57600);
    return 0;
}

