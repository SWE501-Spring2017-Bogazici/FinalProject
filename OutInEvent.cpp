//
// Created by Can Candan on 04/06/17.
//

#include "OutInEvent.h"

OutInEvent::OutInEvent(Simulation *pSimulation, Task *pTask, double time, OutputDevice *pDevice) : Event(pSimulation, pTask, time) {
    this->out=pDevice;
    name="OutInEvent";
}

void OutInEvent::process() {
    log();
    out->work(task, time);
}
