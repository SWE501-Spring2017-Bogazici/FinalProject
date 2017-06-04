//
// Created by Can Candan on 04/06/17.
//

#include "TaskCpuArrivalEvent.h"
#include "Cpu.h"
#include "CpuInEvent.h"

TaskCpuArrivalEvent::TaskCpuArrivalEvent(Simulation *pSimulation, Task *pTask, double time) : Event(pSimulation, pTask,
                                                                                                 time) {
    name="TaskCpuArrivalEvent";

}

void TaskCpuArrivalEvent::process() {
    log();
    Cpu* cpu= sim->getFirstIdleCpu();
    if (cpu) {
        Event* event= new CpuInEvent(sim, task, time, cpu);
        sim->schedule(event);
    } else {
        sim->sjfQueue.push(task);
    }
}
