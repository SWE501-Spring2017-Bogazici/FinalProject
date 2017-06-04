//
// Created by Can Candan on 04/06/17.
//

#ifndef SRC_TASKOUTARRIVALEVENT_H
#define SRC_TASKOUTARRIVALEVENT_H


#include "Simulation.h"
#include "Event.h"

class TaskOutArrivalEvent : public Event{
public:
    TaskOutArrivalEvent(Simulation *pSimulation, Task *pTask, double time);
    void process() override;
};


#endif //SRC_TASKOUTARRIVALEVENT_H
