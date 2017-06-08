//
// Created by Can Candan on 04/06/17.
//

#include "CpuOutEvent.h"
#include "CpuInEvent.h"
#include "TaskOutArrivalEvent.h"


using namespace std;

CpuOutEvent::CpuOutEvent(Simulation *pSimulation, Task *pTask, double time, Cpu *pCpu) : Event(pSimulation, pTask, time) {
    this->cpu=pCpu;
    name="CpuOutEvent";
}

void CpuOutEvent::process() {
    log();
    cpu->setIdle(true);

    Task* newTask= sim->popFromSJFQueue();
    if (newTask) {
        CpuInEvent* event = new CpuInEvent(sim, newTask, time, cpu);
        sim->schedule(event);
    }

    task->setOutTime(time);

    TaskOutArrivalEvent* event= new TaskOutArrivalEvent(sim, task, time);
    sim->schedule(event);
}
