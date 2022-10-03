#ifndef CONFIGDATA_H
#define CONFIGDATA_H


class ConfigData{
    public:
    struct TrottleParam{
        int MinVal;
        int MaxVal;
        int Neutral;
        int DeadZone;
    };
    struct MotorParam{
        float WheelDiameter;    //m
    };
    enum eDriveState{eChild,eTeeny,eAdult,eCracy,eMaxState};
    struct DriveParam{
        eDriveState DriveState;
        float MaxSpeedPerState[eMaxState]; //km/h
        float MaxTorquePerState[eMaxState]; //Nm
    };
    struct AllParam{
        int Initialized;
        struct TrottleParam sTrottleParam;
        struct MotorParam sMotorParam;
        struct DriveParam sDriveParam;
    };

    ConfigData();
    ~ConfigData();

    int Init();
    TrottleParam GetTrottleParam();
    MotorParam GetMotorParam();
    DriveParam GetDriveParam();
    void SetTrottleParam(struct TrottleParam _Param);
    void SetMotorParam(struct MotorParam _Param);
    void SetDriveParam(struct DriveParam _Param);

    private:

    struct AllParam sAllParam;
};

#endif //CONFIGDATA_H