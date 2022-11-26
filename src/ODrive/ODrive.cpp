#include "ODrive.h"
#include "Config/PinConfig.h"

#define AXIS_STATE_CLOSED_LOOP_CONTROL = 0x08
#define IDE_STATE = 0x01 

Odrive::Odrive(ConfigData * _pConfigData){
    Run_Stop = 0;
    pConfigData = _pConfigData;
    BusVoltage = 0;
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
            BusVoltage += ((res.toFloat() - BusVoltage) / 100);
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
                Serial.println(vel_lim);
                String Command_L = "w axis0.controller.config.vel_limit "+ vel_lim + "\n";
                String Command_R = "w axis1.controller.config.vel_limit "+ vel_lim + "\n";
                ODriveSerial->write(Command_L.c_str());
                ODriveSerial->write(Command_R.c_str());
            }
            state = 9;
        }     
    break;
    case 9: //Read odrive error
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
    case 10:
        res = ODriveSerial->readString();
        if(res.length() > 2){
            OdriveError.OdriveError = res.toInt();
            Serial.println(res);
        }else{
            OdriveError.OdriveError = 0xFF;
        }
        state = 11;
    break;
    case 11: //Read Axis 0 error
        while(ODriveSerial->available()){
            ODriveSerial->read();
        }
        ODriveSerial->write("r axis0.error\n");
        state = 12;
    break;
    case 12:
        res = ODriveSerial->readString();
        if(res.length() > 2){
            OdriveError.OdriveAxix0Error = res.toInt();
            Serial.println(res);
        }else{
            OdriveError.OdriveAxix0Error = 0xFFFFFFFF;
        }
        state = 13;
    break;
    case 13: //Read Axis 1 error
        while(ODriveSerial->available()){
            ODriveSerial->read();
        }
        ODriveSerial->write("r axis1.error\n");
        state = 14;
    break;
    case 14:
        res = ODriveSerial->readString();
        if(res.length() > 2){
            OdriveError.OdriveAxis1Error = res.toInt();
            Serial.println(res);
        }else{
            OdriveError.OdriveAxis1Error = 0xFFFFFFFF;
        }
        state = 15;
    break;
    case 15: //Read Axis0.motor error
        while(ODriveSerial->available()){
            ODriveSerial->read();
        }
        ODriveSerial->write("r axis0.motor.error\n");
        state = 16;
    break;
    case 16:
        res = ODriveSerial->readString();
        if(res.length() > 2){
            OdriveError.OdriveAxis0MotorError = res.toInt();
            Serial.println(res);
        }else{
            OdriveError.OdriveAxis0MotorError = 0xFFFFFFFF;
        }
        state = 17;
    break;
    case 17: //Read Axis1.motor error
        while(ODriveSerial->available()){
            ODriveSerial->read();
        }
        ODriveSerial->write("r axis1.motor.error\n");
        state = 18;
    break;
    case 18:
        res = ODriveSerial->readString();
        if(res.length() > 2){
            OdriveError.OdriveAxis1MotorError = res.toInt();
            Serial.println(res);
        }else{
            OdriveError.OdriveAxis1MotorError = 0xFFFFFFFF;
        }
        state = 19;
    break;
    case 19: //Read Controller error
        while(ODriveSerial->available()){
            ODriveSerial->read();
        }
        ODriveSerial->write("r axis0.controller.error\n");
        state = 20;
    break;
    case 20:
        res = ODriveSerial->readString();
        if(res.length() > 2){
            OdriveError.OdriveAxis0ControllerError = res.toInt();
            Serial.println(res);
        }else{
            OdriveError.OdriveAxis0ControllerError = 0xFFFFFFFF;
        }
        state = 21;
    break;
    case 21: //Read Controller error
        while(ODriveSerial->available()){
            ODriveSerial->read();
        }
        ODriveSerial->write("r axis1.controller.error\n");
        state = 22;
    break;
    case 22:
        res = ODriveSerial->readString();
        if(res.length() > 2){
            OdriveError.OdriveAxis1ControllerError = res.toInt();
            Serial.println(res);
        }else{
            OdriveError.OdriveAxis1ControllerError = 0xFFFFFFFF;
        }
        state = 23;
    break;
    case 23: //Read SensorlessEstimator error
        while(ODriveSerial->available()){
            ODriveSerial->read();
        }
        ODriveSerial->write("r axis0.sensorless_estimator.error\n");
        state = 24;
    break;
    case 24:
        res = ODriveSerial->readString();
        if(res.length() > 2){
            OdriveError.OdriveAxis0SensorlessEstimatorError = res.toInt();
            Serial.println(res);
        }else{
            OdriveError.OdriveAxis0SensorlessEstimatorError = 0xFFFFFFFF;
        }
        state = 25;
    break;
    case 25: //Read SensorlessEstimator error
        while(ODriveSerial->available()){
            ODriveSerial->read();
        }
        ODriveSerial->write("r axis1.sensorless_estimator.error\n");
        state = 26;
    break;
    case 26:
        res = ODriveSerial->readString();
        if(res.length() > 2){
            OdriveError.OdriveAxis1SensorlessEstimatorError = res.toInt();
            Serial.println(res);
        }else{
            OdriveError.OdriveAxis1SensorlessEstimatorError = 0xFFFFFFFF;
        }
        state = 27;
    break;
    case 27: //Read encoder error
        while(ODriveSerial->available()){
            ODriveSerial->read();
        }
        ODriveSerial->write("r axis0.encoder.error\n");
        state = 28;
    break;
    case 28:
        res = ODriveSerial->readString();
        if(res.length() > 2){
            OdriveError.OdriveAxis0EncoderError = res.toInt();
            Serial.println(res);
        }else{
            OdriveError.OdriveAxis0EncoderError = 0xFFFFFFFF;
        }
        ReadError = false;
        state = 29;
    break;
    case 29: //Read encoder error
        while(ODriveSerial->available()){
            ODriveSerial->read();
        }
        ODriveSerial->write("r axis1.encoder.error\n");
        state = 30;
    break;
    case 30:
        res = ODriveSerial->readString();
        if(res.length() > 2){
            OdriveError.OdriveAxis1EncoderError = res.toInt();
            Serial.println(res);
        }else{
            OdriveError.OdriveAxis1EncoderError = 0xFFFFFFFF;
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
int Odrive::GetBattCharge(){
    float CellVoltage = BusVoltage/10;
    if(CellVoltage < 3.2){
        return 0;
    }else if(CellVoltage > 4.2){
        return 100;
    }else if(CellVoltage < 3.7){
        return (CellVoltage -3.2)* 20;
    }else if(CellVoltage < 3.9){
        return (CellVoltage -3.7)* 250 + 10;
    }else if(CellVoltage < 4.2){
        return (CellVoltage -3.9)* 133 + 60;
    }
    return 0;
}
float Odrive::GetRPS(){
    return (RPS_L + RPS_R)/2;
}
void Odrive::SetTorque(float torque){
    Torque_L = torque;
    Torque_R = torque;
}

void Odrive::SetMaxSpeed(float Speed){ 
    Serial.println("Max Speed, RPS"); 
    Serial.println(Speed);
    MaxRPS = pConfigData->SpeedToRPS(Speed);
    Serial.println(MaxRPS);
    MaxSpeedUpdate = true;

}
float Odrive::GetMaxSpeed(){
    return pConfigData->RPSToSpeed(MaxRPS);
}

void Odrive::ActualizeOdriveError(){
    if(ReadError == false){
        ReadError = true;
    }
}
Odrive::sOdriveError Odrive::GetOdriveError(bool * BusyWithReading){
    if(ReadError == true){//While reading give 0 
        sOdriveError Error = {0};
        *BusyWithReading = true;
        return Error;
    }else{
        *BusyWithReading = false;
        return OdriveError;
    }
}