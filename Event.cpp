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


ostream &operator<<(ostream &os, const Event &event) {
    os << "time: " << event.time << " task: " << event.task << " sim: " << event.sim;
    return os;
}

bool Event::operator<(const Event &rhs) const {
    cout << "xx" << endl;
    return (time < rhs.time);

}

void Event::log() {
    LOG(INFO) << this->name << " @:" << to_string(this->time) << " t:" << to_string(task->id);
}