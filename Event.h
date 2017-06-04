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
public:
	double time;
	Task* task;
	Simulation* sim;
    string name;

	Event();
	Event(Simulation *sim, Task *task, double time);
	virtual ~Event();
	double getTime() const;
	void setTime(double time);

    void log();


    virtual void process()=0;

    friend ostream &operator<<(ostream &os, const Event &event);

    bool operator<(const Event &rhs) const;
};

#endif /* EVENT_H_ */
