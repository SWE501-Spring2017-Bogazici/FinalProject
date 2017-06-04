/*
 * Task.h
 *
 *  Created on: Jun 2, 2017
 *      Author: Can Candan
 */

#ifndef TASK_H_
#define TASK_H_

class Task {
public:
	int id;
	double arrivalTime;
	double cpuWork;
	double outputWork;
    double waitCpu=0;
    double waitOut=0;
    double cpuServiceStartTime=0;
    double cpuServiceStopTime=0;
    double outtime=0;
    double remainingOutWork=0;
    bool finished;

	Task();
	Task(double arrivalTime, double cpuWork, double outputWork);
	virtual ~Task();
};

#endif /* TASK_H_ */
