//
// Created by Umut Seven on 19.05.2017.
//

#ifndef DES_OUTPUTDEVICE_H
#define DES_OUTPUTDEVICE_H


#include "Task.h"

class OutputDevice {
private:
    double quantum;
    bool idle;
    Task* taskInUse;
    double progress;
    double id;
    double activeTime;
public:
    OutputDevice(double quantum, int id);
    void SetIdle(bool idle);
    bool GetIdle();
    Task* GetTaskInUse();
    void SetTaskInUse(Task *task);
    void DecrementProgress();
    double GetProgress();
    double GetQuantum();
    double GetActiveTime();
    double GetID();
};


#endif //DES_OUTPUTDEVICE_H
