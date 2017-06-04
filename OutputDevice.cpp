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
	if (task->remainingOutWork < quantum) {
		task->outtime = time + task->remainingOutWork;
		activeTime = activeTime + task->remainingOutWork;
        OutFreeEvent* event= new OutFreeEvent(sim, task, task->outtime, this);
        sim->schedule(event);
        task->remainingOutWork=0;
        task->finished=true;
	} else if (task->remainingOutWork == quantum) {
        task->outtime = time + quantum;
        activeTime = activeTime + quantum;
        OutFreeEvent* event= new OutFreeEvent(sim, task, task->outtime, this);
        sim->schedule(event);
        task->remainingOutWork=0;
        task->finished=true;
    } else {
        task->remainingOutWork=task->remainingOutWork-quantum;
        activeTime=activeTime+quantum;
        task->outtime=time+quantum;
        OutFreeEvent* event= new OutFreeEvent(sim, task, task->outtime, this);
        sim->schedule(event);
    }

}

