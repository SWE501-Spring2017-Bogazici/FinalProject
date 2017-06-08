/*
 * OutputDevice.h
 *
 *  Created on: Jun 2, 2017
 *      Author: Can Candan
 */

#include "Task.h"

#ifndef OUTPUTDEVICE_H_
#define OUTPUTDEVICE_H_

class Simulation;

class OutputDevice {
private:
	int id;
	bool idle=true;
	double quantum;
	double activeTime;
	Simulation* sim;

public:
	OutputDevice();
	OutputDevice(int id, double quantum);

	void work(Task* task, double time);

	int getId() const;

	void setId(int id);

	bool isIdle() const;

	void setIdle(bool idle);

	double getQuantum() const;

	void setQuantum(double quantum);

	double getActiveTime() const;

	void setActiveTime(double activeTime);

	Simulation* getSim() const;

	void setSim(Simulation* sim);

	virtual ~OutputDevice();
};

#endif /* OUTPUTDEVICE_H_ */



