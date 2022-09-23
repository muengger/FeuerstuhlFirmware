#ifndef TROTTLE_H
#define TROTTLE_H

class Trottle{
    public:
    Trottle();
    ~Trottle();

    int Init(int _minValue, int _stopValue, int _stopTollerance, int _maxValue);
    int Update();
    int GetTrottleVal();
    private:
    int LowestValue;
    int StopValue;
    int StopTollerance;
    int LastBackwardValue; // Calculated from StopValue & StopTollerance
    int LastForwardValue; // Calculated from StopValue & StopTollerance
    int HighestValue;
    int RawVal;
    int CurrentSpeedPromille;
    bool isForwardFlag;
    int lastInputValue;
};

#endif //TROTTLE_H