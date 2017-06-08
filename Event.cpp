/*
 * Event.cpp
 *
 *  Created on: Jun 2, 2017
 *      Author: Can Candan
 */

#include <iostream>
#include "Event.h"
#include "easylogging++.h"

using namespace std;
Event::Event() {
	// TODO Auto-generated constructor stub
}

Event::Event(Simulation* sim, Task* task, double time) : sim(sim), task(task), time(time) {

}

double Event::getTime() const {
	return time;
}

void Event::setTime(double time) {
	this->time = time;
}

Event::~Event() {
	// TODO Auto-generated destructor stub
}


void Event::log() {
    LOG(INFO) << this->name << " @:" << to_string(this->time) << " t:" << to_string(task->getId());
}

Task *Event::getTask() const {
    return task;
}

void Event::setTask(Task *task) {
    Event::task = task;
}

Simulation *Event::getSim() const {
    return sim;
}

void Event::setSim(Simulation *sim) {
    Event::sim = sim;
}

const string &Event::getName() const {
    return name;
}

void Event::setName(const string &name) {
    Event::name = name;
}

ostream &operator<<(ostream &os, const Event &event) {
    os << "time: " << event.time << " task: " << event.task << " sim: " << event.sim;
    return os;
}