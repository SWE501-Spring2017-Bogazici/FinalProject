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
    activeTime=0.0;
}

Cpu::~Cpu() {
	// TODO Auto-generated destructor stub
}

void Cpu::work(Task *pTask, double time) {
    idle=false;
    double processingTime= pTask->getCpuWork()/freq;
    pTask->setCpuServiceStopTime(time+processingTime);
    activeTime=activeTime+processingTime;
}

int Cpu::getId() const {
    return id;
}

void Cpu::setId(int id) {
    Cpu::id = id;
}

bool Cpu::isIdle() const {
    return idle;
}

void Cpu::setIdle(bool idle) {
    Cpu::idle = idle;
}

double Cpu::getFreq() const {
    return freq;
}

void Cpu::setFreq(double freq) {
    Cpu::freq = freq;
}

double Cpu::getActiveTime() const {
    return activeTime;
}

void Cpu::setActiveTime(double activeTime) {
    Cpu::activeTime = activeTime;
}


