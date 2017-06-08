/*
 * Event.h
 *
 *  Created on: Jun 2, 2017
 *      Author: Can Candan
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <iostream>
#include "Task.h"
#include "Simulation.h"

using namespace std;

class Event {
protected:
	Task* task;

	double time;

	Simulation* sim;

	string name;

public:
	Event();
	Event(Simulation *sim, Task *task, double time);

	virtual void process()=0;

	void log();

	double getTime() const;

	void setTime(double time);

	Task *getTask() const;

	void setTask(Task *task);

	Simulation *getSim() const;

	void setSim(Simulation *sim);

	const string &getName() const;

	void setName(const string &name);

	virtual ~Event();

	friend ostream &operator<<(ostream &os, const Event &event);
};

#endif /* EVENT_H_ */
