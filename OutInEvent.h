//
// Created by Can Candan on 04/06/17.
//

#ifndef SRC_OUTINEVENT_H
#define SRC_OUTINEVENT_H


#include "Event.h"

class OutInEvent : public Event{
private:
    OutputDevice* out;

public:
    OutInEvent(Simulation *pSimulation, Task *pTask, double time, OutputDevice *pDevice);
    void process() override;
};


#endif //SRC_OUTINEVENT_H
