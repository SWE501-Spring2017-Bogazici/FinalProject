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
    cpu->idle=true;
    if (!sim->sjfQueue.empty()) {
        Task* newTask= sim->sjfQueue.top();
        sim->sjfQueue.pop();
        CpuInEvent* event = new CpuInEvent(sim, newTask, time, cpu);
        sim->schedule(event);
    }
    task->outtime= time;
    TaskOutArrivalEvent* event= new TaskOutArrivalEvent(sim, task, time);
    sim->schedule(event);
}
