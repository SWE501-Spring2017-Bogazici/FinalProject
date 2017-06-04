//
// Created by Can Candan on 04/06/17.
//

#ifndef SRC_TASKCPUARRIVALEVENT_H
#define SRC_TASKCPUARRIVALEVENT_H


#include "Event.h"

class TaskCpuArrivalEvent : public Event{

public:
    TaskCpuArrivalEvent(Simulation *pSimulation, Task *pTask, double time);

    void process() override;
};


#endif //SRC_TASKCPUARRIVALEVENT_H
