/*
 * Simulation.cpp
 *
 *  Created on: Jun 2, 2017
 *      Author: Can Candan
 */

#include "Simulation.h"
#include "TaskCpuArrivalEvent.h"
#include "easylogging++.h"
#include <iostream>

using namespace std;

Simulation::Simulation() {
    sjf_queue_max_size=0;
    rr_queue_max_size=0;
    max_active_cpu_id=0;
    max_active_out_id=0;
    average_wait_time=0.0;
    longest_wait_time=0.0;
    average_time_spent=0.0;
    taskCounter=0;
}

Simulation::~Simulation() {
	// TODO Auto-generated destructor stub
}

void Simulation::addCpu(Cpu* cpu) {
	cpus.push_back(cpu);
}

void Simulation::addOutputDevice(OutputDevice* out) {
	out->setSim(this);
	outputDevices.push_back(out);
}

void Simulation::addTask(Task* task) {
	task->setId(taskCounter);
	taskCounter++;
	tasks.push_back(task);
}

void Simulation::schedule(Event* event) {
	futureEventsList.push(event);
}

Task* Simulation::popFromSJFQueue() {
    if (!sjfQueue.empty()) {
        Task* t= sjfQueue.top();
        sjfQueue.pop();
        return t;
    } else {
        return nullptr;
    }
}

Task* Simulation::popFromRRQueue() {
    if (!rrQueue.empty()) {
        Task* t= rrQueue.top();
        rrQueue.pop();
        return t;
    } else {
        return nullptr;
    }
}

void Simulation::run() {
	for (auto task : tasks) {
		TaskCpuArrivalEvent* event= new TaskCpuArrivalEvent(this, task, task->getArrivalTime());
        schedule(event);
	}


	int current_sjf_size=0;
	int current_rr_size=0;

    while (!futureEventsList.empty()) {
        Event* event= futureEventsList.top();
        futureEventsList.pop();
        event->process();
		current_sjf_size=sjfQueue.size();
		if (current_sjf_size>sjf_queue_max_size) {
			sjf_queue_max_size=current_sjf_size;
		}

		current_rr_size=rrQueue.size();
		if (current_rr_size>rr_queue_max_size) {
			rr_queue_max_size=current_rr_size;
		}
    }

	double max_cpu_active_time=0.0;
	for (auto cpu : cpus) {
		if (cpu->getActiveTime()>max_cpu_active_time) {
			max_cpu_active_time=cpu->getActiveTime();
			max_active_cpu_id=cpu->getId();
		}
	}

	double max_out_active_time=0.0;
	for (auto out : outputDevices) {
		if (out->getActiveTime()>max_out_active_time) {
			max_out_active_time=out->getActiveTime();
			max_active_out_id=out->getId();
		}
	}


	double grand_total_wait=0.0;
	double time_spent=0.0;
	double total_time_spent=0.0;
	double total_wait=0.0;
	for (auto t : tasks) {
		time_spent= t->getOutTime()- t->getArrivalTime();
		total_time_spent= total_time_spent+ time_spent;
		total_wait= t->getWaitCpu()+ t->getWaitOut();
		grand_total_wait = grand_total_wait+total_wait;
		if (total_wait>longest_wait_time) {
			longest_wait_time = total_wait;
		}
	}

    average_wait_time = grand_total_wait/tasks.size();
    average_time_spent = total_time_spent/tasks.size();
}

Cpu* Simulation::getFirstIdleCpu() {
	for (auto cpu : cpus) {
		if (cpu->isIdle()) {
			return cpu;
		}
	}
	return nullptr;
}

OutputDevice* Simulation::getFirstIdleOut() {
	for (auto out: outputDevices) {
		if (out->isIdle()) {
			return out;
		}
	}
	return nullptr;
}

void Simulation::addToSJFQueue(Task* task) {
    sjfQueue.push(task);
}

void Simulation::addToRRQueue(Task* task) {
    rrQueue.push(task);
}
