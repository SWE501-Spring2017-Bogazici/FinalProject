//
// Created by Can Candan on 04/06/17.
//

#include "OutFreeEvent.h"
#include "OutInEvent.h"
#include "TaskOutArrivalEvent.h"
#include "easylogging++.h"

OutFreeEvent::OutFreeEvent(Simulation *pSimulation, Task *pTask, double time, OutputDevice *pDevice) : Event(pSimulation, pTask, time) {
    this->out=pDevice;
    name="OutFreeEvent";
}

void OutFreeEvent::process() {
    log();
    out->idle=true;
    if (!task->finished) {
        sim->rrQueue.push(task);
    }


    if (!sim->rrQueue.empty()) {
        Task* newTask= sim->rrQueue.top();
        sim->rrQueue.pop();
        newTask->waitOut=task->waitOut+(time-task->outtime);
        TaskOutArrivalEvent* event= new TaskOutArrivalEvent(sim, newTask, time);
        sim->schedule(event);
    }
}
