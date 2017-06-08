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
private:
	vector<Cpu*> cpus;
    vector<OutputDevice*> outputDevices;
    priority_queue<Event*, vector<Event*>, EventComparator > futureEventsList;
    priority_queue<Task*, vector<Task*> , SJFComparator> sjfQueue;
    priority_queue<Task*, vector<Task*>, RRComparator> rrQueue;

    int taskCounter;
    vector<Task*> tasks;

public:
    int sjf_queue_max_size;
    int rr_queue_max_size;
    int max_active_cpu_id;
    int max_active_out_id;
    double average_wait_time;
    double longest_wait_time;
    double average_time_spent;

	Simulation();

    void addTask(Task* task);

    void addCpu(Cpu* cpu);

    void addOutputDevice(OutputDevice* out);

    Cpu* getFirstIdleCpu();

    OutputDevice* getFirstIdleOut();

    void schedule(Event* event);

    void run();

    void addToRRQueue(Task* task);

    Task* popFromRRQueue();

    void addToSJFQueue(Task* task);

    Task* popFromSJFQueue();

	virtual ~Simulation();
};

#endif /* SIMULATION_H_ */
