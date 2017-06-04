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


public:
	int id;
	bool idle=true;
	double quantum;
	double activeTime;
	Simulation* sim;

	OutputDevice();
	OutputDevice(int id, double quantum);
	virtual ~OutputDevice();
	Simulation* getSim() const;
	void setSim(Simulation* sim);
    void work(Task* task, double time);

};

#endif /* OUTPUTDEVICE_H_ */



