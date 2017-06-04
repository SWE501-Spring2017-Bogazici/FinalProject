//
// Created by Can Candan on 04/06/17.
//

#include "TaskOutArrivalEvent.h"
#include "OutInEvent.h"
#include "easylogging++.h"

TaskOutArrivalEvent::TaskOutArrivalEvent(Simulation *pSimulation, Task *pTask, double time) : Event(pSimulation, pTask, time) {
    name="TaskOutArrivalEvent";
}

void TaskOutArrivalEvent::process() {
    log();
    OutputDevice* out= this->sim->getFirstIdleOut();
    if (out) {
        OutInEvent* event= new OutInEvent(sim, task, time, out);
        sim->schedule(event);
    } else {
        sim->rrQueue.push(this->task);
    }
}
