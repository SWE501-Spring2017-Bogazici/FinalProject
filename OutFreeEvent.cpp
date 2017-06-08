//
// Created by Can Candan on 04/06/17.
//

#include "OutFreeEvent.h"
#include "OutInEvent.h"
#include "TaskOutArrivalEvent.h"
#include "easylogging++.h"

OutFreeEvent::OutFreeEvent(Simulation *pSimulation, Task *pTask, double time, OutputDevice *pDevice) : Event(pSimulation, pTask, time) {
    out=pDevice;
    name="OutFreeEvent";
}

void OutFreeEvent::process() {
    log();
    out->setIdle(true);
    if (!task->isFinished()) {
        sim->addToRRQueue(task);
    }

    Task* newTask= sim->popFromRRQueue();
    if (newTask) {
        newTask->setWaitOut(newTask->getWaitOut()+(time-newTask->getOutTime()));
        TaskOutArrivalEvent* event= new TaskOutArrivalEvent(sim, newTask, time);
        sim->schedule(event);
    }
}
