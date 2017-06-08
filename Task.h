/*
 * Task.h
 *
 *  Created on: Jun 2, 2017
 *      Author: Can Candan
 */

#ifndef TASK_H_
#define TASK_H_

class Task {
private:
	int id;
	double cpuWork;
	double outputWork;
	double waitCpu=0;
	double waitOut=0;

	double cpuServiceStopTime=0;
	double outTime=0;
	double remainingOutWork=0;
	double arrivalTime;
	bool finished;

public:

	Task();

	Task(double arrivalTime, double cpuWork, double outputWork);

	double outputWorked(double time, double quantum);

	double getOutTime() const;

	void setOutTime(double outTime);

	double getArrivalTime() const;

	void setArrivalTime(double arrivalTime);

	bool isFinished() const;

	void setFinished(bool finished);

	double getRemainingOutWork() const;

	void setRemainingOutWork(double remainingOutWork);

	double getCpuWork() const;

	void setCpuWork(double cpuWork);

	double getOutputWork() const;

	void setOutputWork(double outputWork);

	double getWaitCpu() const;

	void setWaitCpu(double waitCpu);

	double getWaitOut() const;

	void setWaitOut(double waitOut);

	double getCpuServiceStopTime() const;

	void setCpuServiceStopTime(double cpuServiceStopTime);

	int getId() const;

	void setId(int id);

	virtual ~Task();
};

#endif /* TASK_H_ */
