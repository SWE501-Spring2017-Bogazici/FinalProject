/*
 * Simulation.cpp
 *
 *  Created on: Jun 2, 2017
 *      Author: Can Candan
 */

#include "Simulation.h"
#include "TaskCpuArrivalEvent.h"
#include <iostream>

using namespace std;

Simulation::Simulation() {
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
	outs.push_back(out);
}

void Simulation::addTask(Task* task) {
	task->id=taskCounter;
	taskCounter++;
	tasks.push_back(task);
}

void Simulation::schedule(Event* event) {
	futureEventsList.push(event);
}

Event* Simulation::popEvent() {
	Event* top= futureEventsList.top();
	futureEventsList.pop();
	return top;
}

void Simulation::run() {
	for (auto task : tasks) {
		TaskCpuArrivalEvent* event= new TaskCpuArrivalEvent(this, task, task->arrivalTime);
        futureEventsList.push(event);
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

	double max_cpu_active_time=0;
	for (auto cpu : cpus) {
		if (cpu->activeTime>max_cpu_active_time) {
			max_cpu_active_time=cpu->activeTime;
			max_active_cpu_id=cpu->id;
		}
	}

	double max_out_active_time=0;
	for (auto out : outs) {
		if (out->activeTime>max_out_active_time) {
			max_out_active_time=out->activeTime;
			max_active_out_id=out->id;
		}
	}


	double grand_total_wait=0.0;
	double time_spent=0.0;
	double total_time_spent=0.0;
	double total_wait=0.0;
	for (auto t : tasks) {
		time_spent= t->outtime - t->arrivalTime;
		total_time_spent= total_time_spent+ time_spent;
		total_wait= t->waitCpu + t->waitOut;
		grand_total_wait = grand_total_wait+total_wait;
		if (total_wait>longest_wait_time) {
			longest_wait_time = total_wait;
			average_wait_time = grand_total_wait/tasks.size();
			average_time_spent = total_time_spent/tasks.size();
		}
	}
}

Cpu* Simulation::getFirstIdleCpu() {
	for (auto cpu : cpus) {
		if (cpu->idle) {
			return cpu;
		}
	}
	return nullptr;
}

OutputDevice* Simulation::getFirstIdleOut() {
	for (auto out: outs) {
		if (out->idle) {
			return out;
		}
	}
	return nullptr;
}

