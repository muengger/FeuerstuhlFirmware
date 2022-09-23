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
    struct AllParam{
        struct TrottleParam sTrottleParam;
    };

    ConfigData();
    ~ConfigData();

    int Init();
    TrottleParam GetTrottleParam();
    void SetTrottleParam(struct TrottleParam _Param);

    private:

    struct AllParam sAllParam;
};

#endif //CONFIGDATA_H