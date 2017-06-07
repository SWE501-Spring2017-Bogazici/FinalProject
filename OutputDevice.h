//
// Created by Umut Seven on 19.05.2017.
//

#ifndef DES_OUTPUTDEVICE_H
#define DES_OUTPUTDEVICE_H


#include "Task.h"
#include "SimulationEntity.h"

class OutputDevice: public SimulationEntity {
private:
    double quantum;
public:
    OutputDevice(double quantum, int id);
    double GetQuantum();
};


#endif //DES_OUTPUTDEVICE_H
