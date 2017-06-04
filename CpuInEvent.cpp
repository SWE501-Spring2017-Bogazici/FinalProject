//
// Created by Can Candan on 04/06/17.
//

#include "CpuInEvent.h"
#include "CpuOutEvent.h"

CpuInEvent::CpuInEvent(Simulation *pSimulation, Task *pTask, double d, Cpu *pCpu) : Event(pSimulation, pTask, d) {
    this->cpu=pCpu;
    name="CpuInEvent";
}

void CpuInEvent::process() {
    log();
    this->task->waitCpu = time - task->arrivalTime;
    this->cpu->work(this->task, time);

    CpuOutEvent* event= new CpuOutEvent(sim, task, task->cpuServiceStopTime, cpu);

    this->sim->schedule(event);
}

