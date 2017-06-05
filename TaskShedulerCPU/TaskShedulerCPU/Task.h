#pragma once
class Task
{
public:
	Task();
	~Task();


private:

public:
	//members that are given from input file
	double arrivalTime;
	double CpuWork;
	double OutputWork;

	//members that are needed by class operations
	bool flag = true;
	int id;
	int assignedCpuID;
	int assignedOutID;
	double burstTime;
	double completionTime = 0;
	double TATime;
	double TotalWaitTime = 0;
	double waitTimeinCPUqueque = 0;
	double waitTimeinOUTqueque = 0;

};


