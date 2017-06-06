// TaskShedulerCPU.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <queue>
#include <vector>
#include <iostream>
#include <functional>
#include <string>
#include <fstream>
#include <list>
#include "Task.h"

using namespace std;
#pragma region CPUClass
struct ResultsOfProgram
{
	int maxLenghtOfFPQ;
	int maxLenghtOfSPQ;
	int idOfGreatestActiveCpu;
	int idOfGreatestActiveOut;
	double avgTime;
	double longesWaitTime;
	double avgTimetoTask;
};
class CPU
{
public:
	CPU(int, double = 1);
	double activeTime;

	void setFreq(double);
	double const getFreq();
	void setCpuID(int);
	int const getCpuID();
	void setActiveTime(double);
	double const getActiveTime();
	void Execute(Task&);
private:
	
	double _freqOfCPU;
	int _cpuID;
};

CPU::CPU(int _id, double _freq) { _cpuID = _id; _freqOfCPU = _freq; }
void CPU::setFreq(double _infreq) { _freqOfCPU = _infreq; }
double const CPU::getFreq() { return _freqOfCPU; }

void CPU::setCpuID(int _inID) { _cpuID = _inID; }
int const CPU::getCpuID() { return _cpuID; }

void CPU::setActiveTime(double _intime)
{
	activeTime = _intime;
}

double const CPU::getActiveTime()
{
	return activeTime;
}

void CPU::Execute(Task& _instance) 
{
	
}
#pragma endregion

#pragma region OutputClass

class Output
{
public:
	Output(int,double = 1);
	~Output();
	void setID(int);
	int const getID(void);
	void setQuantum(double);
	double const getQuantum(void);
public:
	int _id;
	double quantum;
	double activeTime;
};

Output::Output(int id,double quant):_id(id),quantum(quant){}
Output::~Output(){}

void Output::setID(int id)
{
	_id = id;
}

int const Output::getID()
{
	return _id;
}

void Output::setQuantum(double quant)
{
	quantum = quant;
}

double const Output::getQuantum()
{
	return quantum;
}

#pragma endregion
int getNextProcess(std::vector<Task>& tasks, int _time)
{
	int i = 0, low = 0;
	for (i = 0; i<tasks.size(); i++)
		if (tasks[i].flag) { low = i; break; }
	for (i = 0; i<tasks.size(); i++)
		if (tasks[i].flag )
			if (tasks[i].burstTime<tasks[low].burstTime && tasks[i].arrivalTime <= _time)
				low = i;
	return low;
}



#pragma region Comparators
struct LessArrivalTimeSort : public binary_function<Task, Task, bool>
{
	bool operator()( Task const taskN, Task const taskNplus)  const
	{
		//double t1at = taskN->GetArrivalTime();
		//double t2at = taskNplus->GetArrivalTime();
		return taskN.arrivalTime> taskNplus.arrivalTime;
	}
};
struct LessBurstTimeSort : public binary_function<Task, Task, bool>
{
	bool operator() (Task const taskN, Task const taskNplus) const
	{
		return taskN.burstTime> taskNplus.burstTime;

	}
};
bool sortByArrivalTime(Task const taskN, Task const taskNplus)
{
	return taskN.arrivalTime <taskNplus.arrivalTime;
}
bool sortByBurstTime(Task const taskN, Task const taskNplus)
{
	return taskN.burstTime <taskNplus.burstTime;
}
bool sortByAssinedCpuID(Task const taskN, Task const taskNplus)
{
	return taskN.assignedCpuID <taskNplus.assignedCpuID;
}
#pragma endregion
void printTaskQueue(priority_queue<Task, vector<Task>, LessArrivalTimeSort >& q)
{
	while (!q.empty())
	{
		cout << q.top().arrivalTime <<"\t"<< q.top().burstTime<< "\t"<< q.top().id<<endl;
		q.pop();
	}
}
void AssignCpusToTasks(vector<Task>& tasks, vector<CPU> cpus)
{
	int cpuCount = cpus.size();
	int taskCount = tasks.size();
	int cpuIter = 0;
	for(auto t = tasks.begin();t<tasks.end();t++)
	{
		if (cpuIter == cpuCount)cpuIter = 0;
		t->assignedCpuID = cpus.at(cpuIter).getCpuID();
		t->burstTime = (t->CpuWork) / (cpus.at(cpuIter).getFreq());
		++cpuIter;
	}
}
void AssignOutsToTasks(vector<Task>& tasks, vector<Output> Outs)
{
	int outCount = Outs.size();
	int taskCount = tasks.size();
	int outIter = 0;
	for (auto t = tasks.begin(); t<tasks.end(); t++)
	{
		if (outIter == outCount)outIter = 0;
		t->assignedOutID = Outs.at(outIter).getID();
		++outIter;
	}
}

void SortTasksForFArun(vector<Task>& tasks, vector<CPU> cpus)
{
	//Sort Vector to find least arrival time task to execute
	sort(tasks.begin(), tasks.end(), sortByArrivalTime);

	//Assign tasks to CPUs
	AssignCpusToTasks(tasks, cpus);

	//After sort on burst times
	sort(tasks.begin() + 1, tasks.end(), sortByBurstTime);

}
void RunForShortestArrivalTime(vector<Task>& tasks)
{
	double _arrivalTimeOfLessAT = tasks.at(0).arrivalTime;
	double _burstTimeOfLessAT = tasks.at(0).burstTime;
	double _arrivalTimeOfLessBT = tasks.at(1).arrivalTime;

	
	if(_arrivalTimeOfLessBT>_burstTimeOfLessAT)
	{
		double _sumOfAtBt = _arrivalTimeOfLessAT + _burstTimeOfLessAT;
		tasks.at(0).completionTime = _sumOfAtBt;
		tasks.at(0).flag = false;
		for (auto t = tasks.begin() + 1; t < tasks.end(); ++t)
		{
			t->arrivalTime -= _sumOfAtBt;
			t->completionTime += _sumOfAtBt;
		}
	}
	else
	{
		double _sumOfAts = _arrivalTimeOfLessAT + _arrivalTimeOfLessBT;
		tasks.at(0).completionTime = _sumOfAts;
		tasks.at(0).burstTime -= _arrivalTimeOfLessBT;
		for (auto t = tasks.begin() + 1; t < tasks.end(); ++t)
		{
			t->arrivalTime -= _sumOfAts;
			t->completionTime += _sumOfAts;
		}
	}

}
void ShortestJobForCpus(vector<Task> &cpuTaskVector, vector<Task> &outTaskVector, vector<CPU> cpuVector)
{

	sort(cpuTaskVector.begin(), cpuTaskVector.end(), sortByAssinedCpuID);
	
	for (int cpuIndex = 0; cpuIndex < cpuVector.size(); ++cpuIndex)
	{	
		double totalTimeToWork = 0;
		vector<Task> tmpTaskVector;
		for (int i = 0; i < cpuTaskVector.size(); ++i)
		{
			if (cpuTaskVector.at(i).assignedCpuID == cpuIndex +1)
			{
				tmpTaskVector.push_back(cpuTaskVector.at(i));
				//cpuTaskVector.erase(cpuTaskVector.begin()+i);
			}
		}
		double minAt = 999;
		for each (Task _tmp in tmpTaskVector)
		{
			totalTimeToWork += _tmp.burstTime;
			if (_tmp.arrivalTime < minAt)
				minAt = _tmp.arrivalTime;
		}
		
		int time, next = 0, old, i;
		for (time = 0; time<totalTimeToWork; time++)
		{	
			old=next;
			next=getNextProcess(tmpTaskVector,time);
			//if(old!=next || time==0) cout<<"("<<time<<")|==P"<<next+1<<"==|";
			tmpTaskVector[next].burstTime = tmpTaskVector[next].burstTime -1;
			if(tmpTaskVector[next].burstTime <=0) tmpTaskVector[next].flag=false;
			for(i=0;i<tmpTaskVector.size();i++)
				if(i!=next && tmpTaskVector[i].flag && tmpTaskVector[i].arrivalTime<=time)
					tmpTaskVector[i].waitTimeinCPUqueque++;
		}
		for each (Task var in tmpTaskVector)
		{
			var.flag = true;
			outTaskVector.push_back(var);
		}
		cpuVector[cpuIndex].setActiveTime(totalTimeToWork);

	}
}
void RoundRobinForOuts(vector<Task> &outTaskVector,  vector<Task>& processedTaskQue,vector<Output> outVector)
{

	Task taskTmp;
	
	sort(outTaskVector.begin(), outTaskVector.end(), sortByAssinedCpuID);

	for (int outIndex = 0; outIndex < outVector.size(); ++outIndex)
	{
		double totalTimeToWork = 0;
		vector<Task> tmpTaskVector;
		for (int i = 0; i < outTaskVector.size(); ++i)
		{
			if (outTaskVector[i].assignedOutID == outIndex+1)
			{
				tmpTaskVector.push_back(outTaskVector.at(i));
				totalTimeToWork += outTaskVector[i].OutputWork;
			}

		}

		double minAt = 999;
		for each (Task _tmp in tmpTaskVector)
		{
			if (_tmp.arrivalTime < minAt)
				minAt = _tmp.arrivalTime;
		}

		for (double time = minAt; time < totalTimeToWork;)
		{
			for (int i = 0; i<tmpTaskVector.size();++i)
			{
				if (tmpTaskVector[i].arrivalTime <= time && tmpTaskVector[i].flag)
				{
					if (tmpTaskVector[i].OutputWork < outVector[outIndex].quantum)
						minAt = minAt + outVector[outIndex].quantum;
					else
						minAt = minAt + tmpTaskVector[i].OutputWork;

					tmpTaskVector[i].OutputWork = tmpTaskVector[i].OutputWork - outVector[outIndex].getQuantum();
					if (tmpTaskVector[i].OutputWork <= 0) tmpTaskVector[i].flag = false;
					for(int j = 0;j< tmpTaskVector.size();++j)
						if (j != i && tmpTaskVector[j].flag && tmpTaskVector[j].arrivalTime <= minAt)
							tmpTaskVector[j].waitTimeinOUTqueque += (minAt- tmpTaskVector[j].arrivalTime);
					time = time + minAt;
				}

			}
			for each (Task _tmpTask in tmpTaskVector)
			{
				processedTaskQue.push_back(_tmpTask);
			}
		}
		outVector[outIndex].activeTime = totalTimeToWork;
	}
}


vector<string> readFileToVector(const string& filename)
{
	ifstream source;
	source.open(filename);
	vector<string> lines;
	string line;
	while (source >> line)
	{
		lines.push_back(line);
	}
	return lines;
}
bool writeResultsToFile(const string& filename, ResultsOfProgram results)
{
	ofstream source;
	try
	{
		source.open(filename);
		source << results.maxLenghtOfFPQ << endl;
		source << results.maxLenghtOfSPQ << endl;
		source << results.idOfGreatestActiveCpu << endl;
		source << results.idOfGreatestActiveOut << endl;
		source << results.avgTime << endl;
		source << results.longesWaitTime << endl;
	}
	catch (const std::exception&)
	{
		return false;
	}




	return true;
}

//Returns Average time waiting in CPU ready queque
double CalcAvgWaitTimeInQues(vector<Task>& outVector)
{	
	double TAtime = 0;
	double sumOfWaitsInCpuQue = 0;
	for  (int i = 0; i<outVector.size(); ++i)
	{
		//TAtime = outVector[i].completionTime - outVector[i].arrivalTime;
		//outVector[i].waitTimeinCPUqueque = TAtime - outVector[i].burstTime;
		outVector[i].TotalWaitTime = (outVector[i].waitTimeinCPUqueque + outVector[i].waitTimeinOUTqueque);
		sumOfWaitsInCpuQue += outVector[i].TotalWaitTime;
	}
	return (sumOfWaitsInCpuQue / outVector.size());
}
int GetMostActiveCpu(vector<CPU> cpus )
{
	double MostActivetime = 0;
	int MostActiveCpu = 0;
	for each (CPU var in cpus)
	{
		if (MostActivetime<var.activeTime)
		{
			MostActivetime = var.activeTime;
			MostActiveCpu = var.getCpuID();
		}
	}
	return MostActiveCpu +1 ;
}
int GetMostActiveCpu(vector<Output> outs)
{
	double MostActivetime = 0;
	int MostActiveCpu = 0;
	for each (Output var in outs)
	{
		if (MostActivetime<var.activeTime)
		{
			MostActivetime = var.activeTime;
			MostActiveCpu = var._id;
		}
	}
	return MostActiveCpu +1;
}
double GetLongestWaitedTask(vector<Task> tasks)
{
	double LongestWaitingTime = 0;
	int LongestWaitedCpu = 0;
	for each (Task var in tasks)
	{
		if (LongestWaitingTime<var.TotalWaitTime)
		{
			LongestWaitingTime = var.TotalWaitTime;
		}
	}
	return LongestWaitingTime;
}
int main(int argc, char *argv[])
{
	
	string inputFileName("output.txt");

	auto inputValues = readFileToVector(inputFileName);

	ResultsOfProgram results;
	vector<CPU> cpuVector;
	vector<Output> outputVector;
	vector<Task> processedTaskVector;
	vector<Task> cpuTaskVector;
	vector<Task> outTaskVector;


	CPU cpuTemp(0, 0);
	Output outputTemp(0, 0);
	Task taskTemp;
    double freqTemp,quantTemp;
	int cpuNumber, outputNumber,taskNumber,elemIndexer = 0;

 	cpuNumber = stoi(inputValues.at(0));
	for (int i = 0; i<cpuNumber; ++i)
	{
		freqTemp = stod(inputValues.at(i+1));
		cpuTemp.setCpuID(i + 1);
		cpuTemp.setFreq(freqTemp);
		cpuVector.push_back(cpuTemp);
		
	}
	elemIndexer += cpuNumber + 1;
	outputNumber = stoi(inputValues.at(elemIndexer));
	for (int i = 0; i<outputNumber; ++i)
	{
		quantTemp = stod(inputValues.at(elemIndexer + i + 1));
		outputTemp.setID( i + 1);
		outputTemp.setQuantum(quantTemp);
		outputVector.push_back(outputTemp);
	}
	elemIndexer += outputNumber + 1;
	taskNumber = stoi(inputValues.at(elemIndexer));
	for (int i=0;i<taskNumber;++i)
	{
		
		taskTemp.arrivalTime = stod(inputValues.at(elemIndexer + i +1));
		taskTemp.CpuWork = stod(inputValues.at(elemIndexer + i + 2));
		taskTemp.OutputWork = stod(inputValues.at(elemIndexer + i + 3));
		taskTemp.id = i + 1;
		cpuTaskVector.push_back(taskTemp);
		elemIndexer += 2;
	}

	SortTasksForFArun(cpuTaskVector, cpuVector);

	ShortestJobForCpus(cpuTaskVector, outTaskVector ,cpuVector);

	results.avgTime = CalcAvgWaitTimeInQues(outTaskVector);

	AssignOutsToTasks(outTaskVector,outputVector);

	RoundRobinForOuts(outTaskVector, processedTaskVector, outputVector);

#pragma region fillingResults
	results.maxLenghtOfFPQ = (taskNumber / cpuNumber);
	results.maxLenghtOfSPQ = (taskNumber / outputNumber);
	results.idOfGreatestActiveCpu = GetMostActiveCpu(cpuVector);
	results.idOfGreatestActiveOut = GetMostActiveCpu(outputVector);
	results.avgTime = CalcAvgWaitTimeInQues(processedTaskVector);
	results.longesWaitTime = GetLongestWaitedTask(processedTaskVector);
	
	bool flag = writeResultsToFile("output.txt", results);
#pragma endregion




	getchar();
	return 0;
}



