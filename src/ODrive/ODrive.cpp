#include "ODrive.h"
#include "Config/PinConfig.h"

#define AXIS_STATE_CLOSED_LOOP_CONTROL = 0x08
#define IDE_STATE = 0x01 

Odrive::Odrive(ConfigData * _pConfigData){
    Run_Stop = 0;
    pConfigData = _pConfigData;
}
Odrive::~Odrive(){

}

int Odrive::Init(){

    ReadError = false;
    ODriveSerial = &Serial1;
    ODriveSerial->begin(57600);
    ODriveSerial->setTimeout(0);
    MaxRPS = pConfigData->SpeedToRPS(pConfigData->GetDriveParam()->MaxSpeedPerState[pConfigData->GetDriveParam()->DriveState]);
    MaxSpeedUpdate = true;
    return 0;
}

int Odrive::CyclicUpdate(){
    static int state = 0;
    static int old_run_Stop = 0;
    String res;

    switch (state)
    {
    case 0: //Read Bus Voltage Command
        while(ODriveSerial->available()){
            ODriveSerial->read();
        }
        ODriveSerial->write("r vbus_voltage\n");
        state = 1;
    break;
    case 1://Read Bus Voltage Answer
        res = ODriveSerial->readString();
        if(res.length() > 2){
            BusVoltage = res.toFloat();
        }
        state = 2;
    break;
    case 2: //Read revolutions per second Motor 0 Command
        while(ODriveSerial->available()){
            ODriveSerial->read();
        }
        ODriveSerial->write("r axis0.sensorless_estimator.vel_estimate\n");
        state = 3;
    break;
    case 3: //Read revolutions per second Motor 0 Answer
        res = ODriveSerial->readString();
        if(res.length() > 2){
            float fres = res.toFloat();
            if(fres < 0){
                RPS_L = fres * -1;
            }else{
                RPS_L = fres;
            }
        }
        state = 4;
    break;
    case 4://Read revolutions per second Motor 1 Command
        while(ODriveSerial->available()){
            ODriveSerial->read();
        }
        ODriveSerial->write("r axis1.sensorless_estimator.vel_estimate\n");
        state = 5;
    break;
    case 5://Read revolutions per second Motor 1 Answer
        res = ODriveSerial->readString();
        if(res.length() > 2){
            float fres = res.toFloat();
            if(fres < 0){
                RPS_R = fres * -1;
            }else{
                RPS_R = fres;
            }
             
        }
        state = 6;
    break;
    case 6: //Send run ore Stop command if someting has changed
        if(Run_Stop != old_run_Stop){ // State changed => send to drive
            if(Run_Stop){//Start Drive
                ODriveSerial->write("w axis0.requested_state  8\n");
                ODriveSerial->write("w axis1.requested_state  8\n");
            }else{
                ODriveSerial->write("w axis0.requested_state  1\n");
                ODriveSerial->write("w axis1.requested_state  1\n");
            }
            old_run_Stop = Run_Stop;
        }
        state = 7;
    break;
    case 7: // Send new Torque on both motors
        {
            String storque_L(Torque_L,4);
            String storque_R(Torque_R,4);
            String Command_L = "w axis0.controller.input_torque "+ storque_L + "\n";
            String Command_R = "w axis1.controller.input_torque "+ storque_R + "\n";
            ODriveSerial->write(Command_L.c_str());
            ODriveSerial->write(Command_R.c_str());
            state = 8;
        }     
    break;
    case 8: // Send new Max Speed on both motors
        {
            if(MaxSpeedUpdate){
                MaxSpeedUpdate = false;
                String vel_lim(MaxRPS,4);
                //String vel_lim = "20";
                String Command_L = "w axis0.controller.config.vel_limit "+ vel_lim + "\n";
                String Command_R = "w axis1.controller.config.vel_limit "+ vel_lim + "\n";
                ODriveSerial->write(Command_L.c_str());
                ODriveSerial->write(Command_R.c_str());
            }
            state = 9;
        }     
    break;
    case 9: //Read All error
        if(ReadError){
            while(ODriveSerial->available()){
                ODriveSerial->read();
            }
            ODriveSerial->write("r error\n");
            state = 10;
        }else{
            state = 0;
        }
    break;
    case 10://Read revolutions per second Motor 1 Answer
        res = ODriveSerial->readString();
        if(res.length() > 2){
            OdriveError = res.toInt();
        }
        state = 11;
    break;
    case 11: //Read All error
        while(ODriveSerial->available()){
            ODriveSerial->read();
        }
        ODriveSerial->write("r axis0.error\n");
        state = 12;
    break;
    case 12://Read revolutions per second Motor 1 Answer
        res = ODriveSerial->readString();
        if(res.length() > 2){
            OdriveAxix0Error = res.toInt();
        }
        state = 13;
    break;
    case 13: //Read All error
        while(ODriveSerial->available()){
            ODriveSerial->read();
        }
        ODriveSerial->write("r axis1.error\n");
        state = 14;
    break;
    case 14://Read revolutions per second Motor 1 Answer
        res = ODriveSerial->readString();
        if(res.length() > 2){
            OdriveAxix1Error = res.toInt();
        }
        ReadError = false;
        state = 0;
    break;
    case 100:
        Serial.println("BusVoltage");
        Serial.println(BusVoltage);
        Serial.println("RPM_L");
        Serial.println(RPS_L);
        Serial.println("RPM_R");
        Serial.println(RPS_R);
        state = 0;
    break;
    }
    
    
    return 0;
}
int Odrive::Start(){
    Run_Stop = 1;
    return 0;

}
int Odrive::Stop(){
    Run_Stop = 0;
    return 0;
}
float Odrive::GetBusVoltage(){
    return BusVoltage;
}
float Odrive::GetRPS(){
    return (RPS_L + RPS_R)/2;
}
void Odrive::SetTorque(float torque){
    Torque_L = torque;
    Torque_R = torque;
}

void Odrive::SetMaxSpeed(float Speed){  
    MaxRPS = pConfigData->SpeedToRPS(Speed);
    MaxSpeedUpdate = true;

}
float Odrive::GetMaxSpeed(){
    return pConfigData->RPSToSpeed(MaxRPS);
}