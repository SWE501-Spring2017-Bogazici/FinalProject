/*
 * Simulation.h
 *
 *  Created on: Jun 2, 2017
 *      Author: Can Candan
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <vector>
#include <queue>

#include "Cpu.h"
#include "OutputDevice.h"
#include "Task.h"
#include "SJFComparator.h"
#include "RRComparator.h"
#include "Event.h"
#include "EventComparator.h"


class Event;

using namespace std;


class Simulation {
public:

    int sjf_queue_max_size=0;
    int rr_queue_max_size=0;
    int max_active_cpu_id=0;
    int max_active_out_id=0;
    double average_wait_time=0.0;
    double longest_wait_time=0.0;
    double average_time_spent=0.0;

    vector<Cpu*> cpus;
    vector<OutputDevice*> outs;

    priority_queue<Event*, vector<Event*>, EventComparator > futureEventsList;
    priority_queue<Task*, vector<Task*> , SJFComparator> sjfQueue;
    priority_queue<Task*, vector<Task*>, RRComparator> rrQueue;
    vector<Task*> tasks;
    int taskCounter;
	Simulation();
	void addCpu(Cpu* cpu);
	void addOutputDevice(OutputDevice* out);
	void addTask(Task* task);

	void schedule(Event* event);
	Event* popEvent();

	Cpu* getFirstIdleCpu();
    OutputDevice* getFirstIdleOut();
	void run();
	virtual ~Simulation();
};

#endif /* SIMULATION_H_ */
