//
// Created by Umut Seven on 19.05.2017.
//

#ifndef DES_CPU_H
#define DES_CPU_H


#include "Task.h"

class CPU {
private:
    double frequency;
    bool idle;
    Task* taskInUse;
    double progress;
    double id;
    double activeTime;
public:
    CPU(double frequency, int id);
    bool GetIdle();
    void SetIdle(bool idle);
    Task* GetTaskInUse();
    void SetTaskInUse(Task *task);
    void DecrementProgress();
    double GetProgress();
    double GetActiveTime();
    double GetID();
};


#endif //DES_CPU_H
