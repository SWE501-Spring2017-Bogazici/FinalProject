//
// Created by Umut Seven on 07.06.2017.
//

#ifndef DES_SIMULATIONENTITY_H
#define DES_SIMULATIONENTITY_H


#include "Task.h"

// Main class for our entities (CPU & OutputDevice) to derive from
class SimulationEntity {
protected:
    bool idle;
    double progress;
    double id;
    double activeTime;
    Task* taskInUse;
public:
    bool GetIdle();
    void SetIdle(bool idle);
    Task* GetTaskInUse();
    void SetTaskInUse(Task *task);
    void DecrementProgress();
    double GetProgress();
    double GetActiveTime();
    double GetID();
};


#endif //DES_SIMULATIONENTITY_H
