//
// Created by Can Candan on 04/06/17.
//

#ifndef SRC_CPUINEVENT_H
#define SRC_CPUINEVENT_H


#include "Event.h"

class CpuInEvent : public Event{
public:
    Cpu* cpu;
    CpuInEvent(Simulation *pSimulation, Task *pTask, double d, Cpu *pCpu);
    void process() override;


};


#endif //SRC_CPUINEVENT_H
