/*
 * Cpu.h
 *
 *  Created on: Jun 2, 2017
 *      Author: Can Candan
 */

#ifndef CPU_H_
#define CPU_H_

#include "Task.h"

class Cpu {
private:
	int id;
	bool idle=true;
	double freq;
	double activeTime;

public:
	Cpu();
	Cpu(int id, double freq);

	void work(Task *pTask, double time);

	int getId() const;

	void setId(int id);

	bool isIdle() const;

	void setIdle(bool idle);

	double getFreq() const;

	void setFreq(double freq);

	double getActiveTime() const;

	void setActiveTime(double activeTime);

	virtual ~Cpu();
};

#endif /* CPU_H_ */
