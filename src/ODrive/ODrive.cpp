#include "ODrive.h"
#include "Config/PinConfig.h"

//Uart HWSerial (&sercom3, 0, 1, SERCOM_RX_PAD_1, UART_TX_PAD_0);

Odrive::Odrive(void){

}
Odrive::~Odrive(){

}

int Odrive::Init(){


    ODriveSerial = &Serial1;
    odrive = new ODriveArduino(Serial1);
    ODriveSerial->begin(57600);
    ODriveSerial->setTimeout(0);
    return 0;
}

int Odrive::CyclicUpdate(){
    static int state = 0;
    String res;
    switch (state)
    {
    case 0:
        while(ODriveSerial->available()){
            ODriveSerial->read();
        }
        ODriveSerial->write("r vbus_voltage\n");
        state = 1;
    break;
    case 1:
        res = ODriveSerial->readString();
        if(res.length() > 2){
            BusVoltage = res.toFloat();
        }
        state = 2;
    break;
    case 2:
        while(ODriveSerial->available()){
            ODriveSerial->read();
        }
        ODriveSerial->write("r axis0.sensorless_estimator.vel_estimate\n");
        state = 3;
    break;
    case 3:
        res = ODriveSerial->readString();
        if(res.length() > 2){
            RPM_L = res.toFloat();
        }
        state = 4;
    break;
    case 4:
        while(ODriveSerial->available()){
            ODriveSerial->read();
        }
        ODriveSerial->write("r axis1.sensorless_estimator.vel_estimate\n");
        state = 5;
    break;
    case 5:
        res = ODriveSerial->readString();
        if(res.length() > 2){
            RPM_R = res.toFloat();
        }
        state = 6;
    break;
    case 6:
        Serial.println("BusVoltage");
        Serial.println(BusVoltage);
        Serial.println("RPM_L");
        Serial.println(RPM_L);
        Serial.println("RPM_R");
        Serial.println(RPM_R);
        state = 0;
    break;
    }
    
    
    return 0;
}
int Odrive::Start(){
    return 0;

}
int Odrive::Stop(){

    return 0;
}
float Odrive::GetBusVoltage(){
    return BusVoltage;

}
float Odrive::GetRPM(){
    return 0;
}

