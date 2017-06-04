/*
 * Cpu.cpp
 *
 *  Created on: Jun 2, 2017
 *      Author: Can Candan
 */

#include "Cpu.h"
#include <iostream>

using namespace std;

Cpu::Cpu(int id, double freq) : id(id), freq(freq) {}

Cpu::Cpu() {
	// TODO Auto-generated constructor stub

}

Cpu::~Cpu() {
	// TODO Auto-generated destructor stub
}

void Cpu::work(Task *pTask, double time) {
    idle=false;
    pTask->cpuServiceStartTime=time;
    double processingTime= pTask->cpuWork/freq;
    pTask->cpuServiceStopTime=time+processingTime;
    activeTime=activeTime+processingTime;
}


