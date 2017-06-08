//
// Created by Can Candan on 04/06/17.
//

#ifndef SRC_OUTFREEEVENT_H
#define SRC_OUTFREEEVENT_H


#include "Event.h"

class OutFreeEvent : public Event{
private:
    OutputDevice* out;
public:
    OutFreeEvent(Simulation *pSimulation, Task *pTask, double time, OutputDevice *pDevice);
    void process() override;
};


#endif //SRC_OUTFREEEVENT_H
