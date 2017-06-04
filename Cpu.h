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
public:
	int id;
	bool idle=true;
	double freq;
	double activeTime;

	Cpu();
	Cpu(int id, double freq);

    void work(Task *pTask, double time);
	virtual ~Cpu();


};

#endif /* CPU_H_ */
