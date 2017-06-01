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
public:
    CPU(double frequency);
    bool GetIdle();
    void SetIdle(bool idle);
    Task* GetTaskInUse();
    void SetTaskInUse(Task *task);
    void DecrementProgress();
    double GetProgress();
};


#endif //DES_CPU_H
