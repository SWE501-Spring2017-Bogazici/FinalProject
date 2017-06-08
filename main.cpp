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
	bool operator() (Tag &lhs, Tag &rhs){
		if(lhs.time != rhs.time) return (lhs.time > rhs.time);
		else return (lhs.index > rhs.index); }
};

struct myCPUComp{
	bool operator() (Tag &lhs, Tag &rhs){
		if(lhs.dProc != rhs.dProc) return (lhs.dProc > rhs.dProc); 
		else return (lhs.index > rhs.index); }
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
		if(tn<TIME[2]){ cout << "Trouble@Task.Complete()" << endl; return; }
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

//accepts a tag, "works" on Task pointed by it,
//increases its time and returns tag

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

//accepts a tag, "works" on Task pointed by it,
//increases its time and (if complete) its location and returns tag
//doesn't check currentLocation, assumed to be 5
	Tag Work(Tag &_tag){
		_tag.time = (_tag.locator)->OutFetched(_tag.time, quanta);
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
		_tag.currentLocation = 6;
		int i = _tag.vIndex;
		WaitTime[i] = vTask[i].WaitTime();
		TaskTime[i] = vTask[i].TaskTime();
	}
	
	double maxWaitTime(){
		double max = 0;
		for(int i=0; i<size; i++){ if(WaitTime[i] > max) max = WaitTime[i]; }
		return max;
	}
	double avWaitTime(){
		double sum = 0;
		for(int i=0; i<size; i++){ sum += WaitTime[i]; }
		return (sum/size);
	}
	double avTaskTime(){
		double sum = 0;
		for(int i=0; i<size; i++){ sum += TaskTime[i]; }
		return (sum/size);
	}

	pqTComp GenerateQueue(){
		pqTComp que;
		for(int i=0; i<size; i++){
			Tag temp = vTask[i].initTag();
			temp.vIndex = i;
			que.push(temp);
		}
		return que;
	}
};

/*two classes that are basically queues that receive and extract tags
//currentLocation is updated when receiving and NOT when extracting*/
class pCPUQueue{
	pqCComp preCpu; int maxL = 0;
public:
	Tag top(){ Tag rslt = preCpu.top(); preCpu.pop(); return rslt; }
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
	Tag top(){ Tag rslt = preOut.top(); preOut.pop(); return rslt; }
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
	int size=0, workingCpu = 0;
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

//both expecterd to return if there is some cpu that is idle
	bool isIdle(){ if((workingCpu<size)!=(isLongIdle())) cout << "TROUBLE@aCPU.isIdle()" << endl; //TESTLINE
		return (workingCpu < size); }
	bool isLongIdle(){
		bool rslt = false;
		for(int i=0; i<size; i++){ rslt = (rslt || !(vCPU[i].isActive())); }
		return rslt;
	}
	
	Tag activate(Tag &_tag){ //accepts a tag, puts it to work at first available cpu, receives result
		workingCpu++;
		int i = 0;
		_tag.currentLocation = 3;
		for(; i<size; i++){ if(!(vCPU[i].isActive())) break; }
		_tag.index = i;
		vCPU[i].Start(_tag.time);
		return vCPU[i].Work(_tag);
	}

//puts cpu that was working on Tn to idle... //CAREFUL
	void idle(Tag const &Tn){
		workingCpu--;
		vCPU[Tn.index].Stop(Tn.time);
	}

//tag _done is done, cpu working on it recieves another //CAREFUL
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
	int size=0, workingOut = 0;
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
	
//both expecterd to return if there is some output that is idle
	bool isIdle(){ if((workingOut<size)!=(isLongIdle())) cout << "TROUBLE@aOut.isIdle()" << endl; //TESTLINE
		return (workingOut < size); }
	bool isLongIdle(){
		bool rslt = false;
		for(int i=0; i<size; i++){ rslt = (rslt || !(vOut[i].isActive())); }
		return rslt;
	}

	Tag activate(Tag &_tag){
		workingOut++;
		int i = 0;
		_tag.currentLocation = 5;
		for(; i<size; i++){ if(!(vOut[i].isActive())) break; }
		_tag.index = i;
		vOut[i].Start(_tag.time);
		return vOut[i].Work(_tag);
	}
	
//CAREFUL
	void idle(Tag const &Tn){
		workingOut--;
		vOut[Tn.index].Stop(Tn.time); }
	
//CAREFUL
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
	
	void getWorkTimes(){ for(int i=0; i<size; i++) WorkTime[i] = vOut[i].Stop(0); }
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
		GlobalCounter = aTask.GenerateQueue(); //indices are 0, vIndices are not
		/*GlobalCounter counts all the tasks in aTask, aCPU, aOut
		//so if it's empty, all tasks are complete
		//which in turn means: DON'T PUT TASKS BACK IF THEY ARE COMPLETED!
		//which in turn allows us to assume: all the tasks inside are INCOMPLETE*/
		while(!(GlobalCounter.empty())){
			Tag current = GlobalCounter.top();
			GlobalCounter.pop();
			switch(current.currentLocation){ //where was topmost element located?
			/*once again, GlobalCurrent counts tags in arrays and not queues,
			//therefore we can assume all locations are 1, 3 or 5*/
				case 1: 
					if(aCPU.isIdle()) GlobalCounter.push( aCPU.activate(current) );
					/*there is an idle CPU
					//CPUArray.activate() accepts a tag that WAS in task array,
					//TRANSFORMS IT into a tag that IS in CPUArray and pushes back to GlobalCounter*/
					else pCq.receive(current);
					/*pCq.receive() accepts a tag that WAS in task array
					//TRANSFORMS IT into a tag that IS in pCq
					//doesn't return the tag*/
					break;
					
				case 3:
					/*now, time has come for an element to leave aCPU
					//which MEANS, it's also time to determine what is coming in*/
					if(!(pCq.empty())) GlobalCounter.push( aCPU.receive(current) );
					/*if there are elements in pCq, receive from there
					//why do we ignore elements in aTask? because a task in
					//motion cannot be in aTask, when they start moving, they'll either
					//directly go to aCPU, or to pCq
					//also, receive() DOES NOT change its variable*/
					else aCPU.idle(current);
					/*so now we see, aCPU.idle() accepts a tag: that tag is LEAVING the array
					//and since there are no more elements left waiting, it's time for that
					//CPU to go idle. note that, idle() DOES NOT change its variable*/
					
					//onwards to deciding where that tag leaving aCPU goes: directly to aOut or pOq?
					if(aOut.isIdle()) GlobalCounter.push( aOut.activate(current) );
					/*so now demand is: aOut.activate() accepts tags and
					//TRANSFORMS them into tags that are IN aOut
					//OR, we need to make sure that variables passed into it are
					//CERTAINLY in aOut*/
					else pOq.receive(current);
					/*similar to pCq.receive() above, it accepts and TRANSFORMS
					//and doesn't return any tag*/
					break;
					
				case 5:
					/*let's cut it short: first 2 lines: deciding where the tag leaving aOut is going
					//but FIRST we need to check if job is finished
					//if it's finished, we'll set currentLocation to 6, won't push it back,
					//receive new tag or simply go idle
					//if it's not finished, then we'll check pOq, if it's empty we'll repeat
					//if pOq is nonempty, then we'll put it to pOq and then get the next item
					//note that, "if empty we repeat" part is equivalent to
					//"put it to pOq and get the next item"
					//(actually, don't do that: we may get MaxQueueLength=1 in cases it's actually =0) 
					//therefore we can just say: "if not finished put to pOq, get the first item"
					//note that pOq doesn't care of tag's time, so we need to adjust time accordingly*/
					if((current.locator)->isComplete()){
						aTask.TaskComplete(current);
						if(pOq.empty()) aOut.idle(current);
						else GlobalCounter.push( aOut.receive(current) );
					}
					else {
						if(pOq.empty()) GlobalCounter.push( aOut.repeat(current) );
						else {
							pOq.receive(current);
							GlobalCounter.push( aOut.receive(current) );
						}
					}
					
					
					//OLD, INFINITELY-LOOPING VERSION
					/*if(!(pOq.empty())) GlobalCounter.push( aOut.receive(current) );
					
					else { aOut.idle(current); }
					
					if((current.locator)->isComplete()){ aTask.TaskComplete(current); }
					else if(!(pOq.empty())) pOq.receive(current);
					else GlobalCounter.push( aOut.repeat(current) );*/
					break;
				default: cout << "TROUBLE! at switch(currentLocation)" << endl; break;
			}
			
		}
		aCPU.getWorkTimes();
		aOut.getWorkTimes();
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
