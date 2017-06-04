/*
 * Task.cpp
 *
 *  Created on: Jun 2, 2017
 *      Author: Can Candan
 */

#include "Task.h"

Task::Task() {
	// TODO Auto-generated constructor stub

}

Task::Task(double arrivalTime, double cpuWork, double outputWork) : arrivalTime(arrivalTime), cpuWork(cpuWork), outputWork(outputWork) {
    remainingOutWork=outputWork;
    finished=false;
}



Task::~Task() {
	// TODO Auto-generated destructor stub
}

