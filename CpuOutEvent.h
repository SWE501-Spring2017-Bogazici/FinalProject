//
// Created by Can Candan on 04/06/17.
//

#ifndef SRC_CPUOUTEVENT_H
#define SRC_CPUOUTEVENT_H


#include "Event.h"

class CpuOutEvent : public Event{

public:
    Cpu* cpu;
    CpuOutEvent(Simulation *pSimulation, Task *pTask, double time, Cpu *pCpu);

    void process() override;
};


#endif //SRC_CPUOUTEVENT_H
