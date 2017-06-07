//
// Created by Umut Seven on 19.05.2017.
//

#ifndef DES_CPU_H
#define DES_CPU_H


#include "Task.h"
#include "SimulationEntity.h"

class CPU :public SimulationEntity{
private:
    double frequency;
public:
    CPU(double frequency, int id);
};


#endif //DES_CPU_H
