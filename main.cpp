#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <array>
#include <queue>

using namespace std;

/*through the code, t[-] stands for time.
//idea is: events are happening specific times, and we don't actually "have" other times.
//so an event happens at time tn, and from there we can compute time that it'll complete, tm.
//thus most events have a double t0 as input, and return t1.*/

class Task;
class Processor;
class Output;
class TaskArray;
class CPUArray;
class OutArray;
class pCPUQueue;
class pOutQueue;
class Setting;

struct Tag{
	double time; int index; Task* locator; int currentLocation; double dProc; int vIndex;
};
ostream& operator<<(ostream& out, Tag& _t){
	out << _t.time << " " << _t.currentLocation << " " << _t.index << " " << _t.dProc << " " << _t.vIndex << endl;
	return out;
}

struct myTimeComp{
	bool operator() (Tag &lhs, Tag &rhs){ return (lhs.time > rhs.time); }
};

struct myCPUComp{
	bool operator() (Tag &lhs, Tag &rhs){ return (lhs.dProc > rhs.dProc); }
};

typedef priority_queue<Tag, vector<Tag>, myTimeComp> pqTComp;
typedef priority_queue<Tag, vector<Tag>, myCPUComp> pqCComp;

class Task{
	double TIME[4] = {0, -1, -2, -3}; //stands for entry time into first queue, into CPU, into second queue, job completion
	double DEMAND[2] = {0, 0};
	double STATS[4] = {0, 0, 0, 0}; //stands for time spent in Q1, in CPU, in Output, in Q2
	double C_time = 0, O_rem = 0;
	bool _iscomplete = false;
public:
	bool isComplete(){ return _iscomplete; }
	double WaitTime(){ if(_iscomplete) return STATS[0]+STATS[3]; }
	double TaskTime(){ if(_iscomplete) return TIME[3]-TIME[0]; }
	
	void Complete(double tn){
		if(tn<0){ return; }
		TIME[3] = tn;
		STATS[0] = TIME[1]-TIME[0];
		STATS[1] = C_time;
		STATS[2] = DEMAND[1];
		STATS[3] = TIME[3]-(TIME[2]+STATS[2]);
		_iscomplete = true;
	}
	
	double CPUFetched(double t0, double freq){
		TIME[1] = t0;
		C_time = DEMAND[0]/freq;
		TIME[2] = TIME[1] + C_time;
		return TIME[2];
	}
	
	double OutFetched(double t0, double quant){
		if(O_rem>quant){ O_rem -= quant; return t0+quant; }
		else { double end = t0+O_rem; O_rem = 0; Complete(end); return end; }
	}
	
	Tag initTag(){
		Tag _temp = { TIME[0], 0, this, 1, DEMAND[0], 0 };
		return _temp;
	}
	
	Task(double t_arrival, double dem_CPU, double dem_O){
		TIME[0] = t_arrival;
		DEMAND[0] = dem_CPU;
		DEMAND[1] = dem_O;
		O_rem = dem_O;
	}
};

class Processor{
	double freq, activeTime = 0, t_working = 0;
	bool _active = false;
public:
	void Start(double t0){ t_working = t0; _active = true; }
	double Stop(double tn){ if(tn>t_working) activeTime += (tn - t_working); _active = false; return activeTime; }
	bool isActive(){ return _active; }
	
	Tag Work(Tag &_tag){
		_tag.time = (_tag.locator)->CPUFetched(_tag.time, freq);
		return _tag;
	}
	
	Processor(double in){ if(in>0) freq = in; }
};

class Output{
	double quanta, activeTime = 0, t_working = 0;
	bool _active = false;
public:
	void Start(double t0){ t_working = t0; _active = true; }
	double Stop(double tn){ if(tn>t_working) activeTime += (tn - t_working); _active = false; return activeTime; }
	bool isActive(){ return _active; }
	
	Tag Work(Tag &_tag){
		_tag.time = (_tag.locator)->OutFetched(_tag.time, quanta);
		if((_tag.locator)->isComplete()) _tag.currentLocation = 6;
		return _tag;
	}
	
	Output(double in){ if(in>0) quanta = in; }
};

class TaskArray{
	vector<Task> vTask;
	vector<double> WaitTime, TaskTime;
	int size=0;
public:
	TaskArray(){};
	TaskArray(int n, ifstream &ifs){
		size = n;
		for(int i=0; i<size; i++){
			double t_arr, w_CPU, w_Out;
			ifs >> t_arr >> w_CPU >> w_Out;
			vTask.push_back( Task(t_arr, w_CPU, w_Out) );
		}
		WaitTime.resize(size);
		TaskTime.resize(size);
	}
	
	void TaskComplete(Tag &_tag){
		int i = _tag.vIndex;
		WaitTime[i] = vTask[i].WaitTime();
		TaskTime[i] = vTask[i].TaskTime();
	}
	
	double avWaitTime(){
		double sum = 0;
		for(int i=0; i<size; i++){ sum += WaitTime[i]; }
		return (sum/size);
	}
	double maxWaitTime(){
		double max = 0;
		for(int i=0; i<size; i++){ if(WaitTime[i] > max) max = WaitTime[i]; }
		return max;
	}
	double avTaskTime(){
		double sum = 0;
		for(int i=0; i<size; i++){ sum += TaskTime[i]; }
		return (sum/size);
	}

	pqTComp GenerateQueue(){
		pqTComp que;
		cout << "Initial setting:\n"; //TESTLINE
		for(int i=0; i<size; i++){
			Tag temp = vTask[i].initTag();
			temp.vIndex = i;
			que.push(temp);
			cout << temp; //TESTLINE
		}
		return que;
	}
};

class pCPUQueue{
	pqCComp preCpu; int maxL = 0;
public:
	Tag top(){ return preCpu.top(); preCpu.pop(); }
	bool empty(){ return preCpu.empty(); }
	int maxLength(){ return maxL; }
	
	void receive(Tag &_tag){
		_tag.currentLocation = 2;
		preCpu.push(_tag);
		if(preCpu.size()>maxL) maxL = preCpu.size();
	}
};

class pOutQueue{
	pqTComp preOut; int maxL = 0;
public:
	Tag top(){ return preOut.top(); preOut.pop(); }
	bool empty(){ return preOut.empty(); }
	int maxLength(){ return maxL; }
	
	void receive(Tag &_tag){
		_tag.currentLocation = 4;
		preOut.push(_tag);
		if(preOut.size()>maxL) maxL = preOut.size();
	}
};

class CPUArray{
	pCPUQueue* pCq;
	vector<Processor> vCPU;
	vector<double> WorkTime;
	int size=0;
public:
	CPUArray(){ pCq = nullptr; }
	CPUArray(int n, ifstream &ifs, pCPUQueue*_pcq){
		pCq = _pcq;
		size = n;
		for(int i=0; i<size; i++){
			double freq; 
			ifs >> freq; 
			vCPU.push_back( Processor(freq) );
		}
		WorkTime.resize(size);
	}
	
	Tag activate(Tag &_tag){
		int i = 0;
		_tag.currentLocation = 3;
		for(; i<size; i++){ if(!(vCPU[i].isActive())) break; }
		_tag.index = i;
		vCPU[i].Start(_tag.time);
		return vCPU[i].Work(_tag);
	}
	
	void idle(Tag &Tn){
		Tn.currentLocation++;
		vCPU[Tn.index].Stop(Tn.time); }
	
	Tag receive(Tag const &_done){
		Tag _new = (pCq->top());
		_new.index = _done.index;
		_new.time = _done.time;
		_new.currentLocation = 3;
		return vCPU[_new.index].Work(_new);
	}
	
	void getWorkTimes(){ for(int i=0; i<size; i++) WorkTime[i] = vCPU[i].Stop(0); }
	int longestWorker(){
		double max = 0; int maxIndex = 0;
		for(int i=0; i<size; i++){
			if(WorkTime[i]>max){
				max = WorkTime[i];
				maxIndex = i;
			}
		}
		return maxIndex+1;
	}
	
};

/* at this point, it's clear that some sort of templating/inheritance 
 * regarding OutArray/CPUArray would help to shorten the code;
 * but as they say: "shortest path is the well-known one"! */
class OutArray{
	pOutQueue* pOq;
	vector<Output> vOut;
	vector<double> WorkTime;
	int size=0;
public:
	OutArray(){ pOq = nullptr; }
	OutArray(int n, ifstream &ifs, pOutQueue*_poq){
		pOq = _poq;
		size = n;
		for(int i=0; i<size; i++){
			double quanta;
			ifs >> quanta;
			vOut.push_back( Output(quanta) );
		}
		WorkTime.resize(size);
	}
	
	Tag activate(Tag &_tag){
		int i = 0;
		_tag.currentLocation = 5;
		for(; i<size; i++){ if(!(vOut[i].isActive())) break; }
		_tag.index = i;
		vOut[i].Start(_tag.time);
		return vOut[i].Work(_tag);
	}
	
	void idle(Tag &Tn){
		Tn.currentLocation++;
		vOut[Tn.index].Stop(Tn.time); }
	
	Tag receive(Tag const &_done){
		Tag _new = pOq->top();
		_new.index = _done.index;
		_new.time = _done.time;
		_new.currentLocation = 5;
		return vOut[_new.index].Work(_new);
	}
	
	Tag repeat(Tag &again){
		return vOut[again.index].Work(again);
	}
	
	int longestWorker(){
		double max = 0; int maxIndex = 0;
		for(int i=0; i<size; i++){
			if(WorkTime[i]>max){
				max = WorkTime[i];
				maxIndex = i;
			}
		}
		return maxIndex+1;
	}
	
};

class Setting{
	int nTask, nCPU, nOutput;
	TaskArray aTask;
	CPUArray aCPU;
	OutArray aOut;
	pCPUQueue pCq;
	pOutQueue pOq;
	pqTComp GlobalCounter;
	
	int workingCPU = 0, workingOut = 0;
public:
	Setting(char* fileloc){
		ifstream inputFile;
		inputFile.open(fileloc, ifstream::in);
		inputFile >> nCPU;
		aCPU = CPUArray(nCPU, inputFile, &pCq);
		inputFile >> nOutput;
		aOut = OutArray(nOutput, inputFile, &pOq);
		inputFile >> nTask;
		aTask = TaskArray(nTask, inputFile);
		inputFile.close();
	}
	
	void Work(){
		GlobalCounter = aTask.GenerateQueue();
		while(!(GlobalCounter.empty())){
			Tag current;
			do{
				current = GlobalCounter.top();
				cout << current;
				GlobalCounter.pop();
			} while(!(GlobalCounter.empty()) && current.currentLocation >= 6);
			cout << "Going with this current;\n"; //TESTLINE
			switch(current.currentLocation){
				case 1: 
					cout << "in case 1;\n";
					if(workingCPU<nCPU){
					cout << "workingCPU/nCPU are: " << workingCPU << " " << nCPU << endl;
					GlobalCounter.push( aCPU.activate(current) );
					workingCPU++; }
					else pCq.receive(current); break;
					
				case 3: if(!(pCq.empty())) GlobalCounter.push( aCPU.receive(current) );
					else { aCPU.idle(current); workingCPU--; }
					
					if(workingOut<nOutput){
					GlobalCounter.push( aOut.activate(current) );
					workingOut++; }
					else pOq.receive(current); break;
					
				case 5: if(!(pOq.empty())) GlobalCounter.push( aOut.receive(current) );
					else { aOut.idle(current); workingOut--; }
					
					if((current.locator)->isComplete()){ aTask.TaskComplete(current); }
					else if(!(pOq.empty())) pOq.receive(current);
					else GlobalCounter.push( aOut.repeat(current) );
					break;
				default: break;
			}
			
		}
	}
	
	void ExtractResults(char* fileloc){
		ofstream outputFile;
		outputFile.open(fileloc);
		outputFile << pCq.maxLength() << endl;
		outputFile << pOq.maxLength() << endl;
		outputFile << aCPU.longestWorker() << endl;
		outputFile << aOut.longestWorker() << endl;
		outputFile << aTask.avWaitTime() << endl;
		outputFile << aTask.maxWaitTime() << endl;
		outputFile << aTask.avTaskTime() << endl;
		outputFile.close();
	}
};

int main(int argc, char *argv[])
{
	if(argc!=3){ // not as specified
		cerr << "Usage: " << argv[0] << " SOURCE DESTINATION" << endl;
		return 1;
	}
	
	Setting Project(argv[1]);
	Project.Work();
	Project.ExtractResults(argv[2]);
	return 0;
}
