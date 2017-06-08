/*
 * OutputDevice.cpp
 *
 *  Created on: Jun 2, 2017
 *      Author: Can Candan
 */

#include "OutputDevice.h"
#include "OutFreeEvent.h"
#include "easylogging++.h"


OutputDevice::OutputDevice() {
	// TODO Auto-generated constructor stub
}

OutputDevice::OutputDevice(int id, double quantum) : id(id), quantum(quantum) {
    activeTime=0.0;
}

Simulation* OutputDevice::getSim() const {
	return sim;
}

void OutputDevice::setSim(Simulation* sim) {
	this->sim = sim;
}

OutputDevice::~OutputDevice() {
	// TODO Auto-generated destructor stub
}

void OutputDevice::work(Task *task, double time) {
	this->idle=false;
    double worked=task->outputWorked(time, quantum);
    activeTime = activeTime + worked;
    OutFreeEvent* event= new OutFreeEvent(sim, task, task->getOutTime(), this);
    sim->schedule(event);
}

int OutputDevice::getId() const {
    return id;
}

void OutputDevice::setId(int id) {
    OutputDevice::id = id;
}

bool OutputDevice::isIdle() const {
    return idle;
}

void OutputDevice::setIdle(bool idle) {
    OutputDevice::idle = idle;
}

double OutputDevice::getQuantum() const {
    return quantum;
}

void OutputDevice::setQuantum(double quantum) {
    OutputDevice::quantum = quantum;
}

double OutputDevice::getActiveTime() const {
    return activeTime;
}

void OutputDevice::setActiveTime(double activeTime) {
    OutputDevice::activeTime = activeTime;
}

