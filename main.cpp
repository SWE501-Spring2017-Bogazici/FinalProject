#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "CPU.h"
#include "OutputDevice.h"

using namespace std;

vector<string> ParseInput(string inputPath);

vector<CPU> CreateCPUs(vector<string> lines);

vector<OutputDevice> CreateOutputDevices(vector<string> lines);

vector<Task> CreateTasks(vector<string> lines);

vector<string> SplitString(string main, char sep);

template<class T>
vector<T> CreateEntityVector(vector<string> lines);

template<class T>
int GetIdOfEntityHighestWork(vector<T> entities);

string Simulate(vector<CPU> cpus, vector<Task> tasks, vector<OutputDevice> outputDevices);

Task *GetTaskByArrivalTime(double i, vector<Task> tasks);

CPU *FindAvailableCPU(vector<CPU> &cpus);

Task *FindTaskWithShortestWork(vector<Task> &queue);

OutputDevice *FindAvailableOutputDevice(vector<OutputDevice> &devices);

void CreateOutput(string path, string result);

void RemoveTaskFromVector(double id, vector<Task> &vec);

double CalculateAverageWaitTime(vector<int> waitTimes);

const int MAX_TIME = 10000;

int main(int argc, char **argv) {

    // Check if arguments are valid
    if (argc < 3) {
        cout << "Please give the input file & the output file as arguments." << endl;
        return 0;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];

    vector<string> lines = ParseInput(inputFile);
    vector<CPU> cpus = CreateCPUs(lines);
    printf("Read %lu CPU's\n", cpus.size());

    // Remove CPU lines from input vector
    lines.erase(lines.begin(), lines.begin() + cpus.size() + 1);

    vector<OutputDevice> outputDevices = CreateOutputDevices(lines);
    printf("Read %lu output devices.\n", outputDevices.size());

    // Remove output device lines from input vector
    lines.erase(lines.begin(), lines.begin() + outputDevices.size() + 1);

    vector<Task> tasks = CreateTasks(lines);
    printf("Read %lu tasks.\n", tasks.size());

    string result = Simulate(cpus, tasks, outputDevices);

    CreateOutput(outputFile, result);
    return 0;
}

string Simulate(vector<CPU> cpus, vector<Task> tasks, vector<OutputDevice> outputDevices) {
    vector<Task> queue;
    vector<Task> outputQueue;

    vector<int> waitTimes;

    // Output variables
    string maxLengthQueue;
    string maxLengthOutputQueue;
    string idOfCPUGreatest;
    string idOfOutputGreatest;
    string averageWaitTime;
    string longestWaitTime;
    string averageTime;

    int queueMax = 0;
    int pQueueMax = 0;

    // Time
    double i = 0;

    // Main event loop
    while (i <= MAX_TIME) {
        // Get task
        Task *task = GetTaskByArrivalTime(i, tasks);

        if (task != NULL) {
            queue.push_back(*task);
            queueMax++;

            printf("Task added to priority queue.");
        }

        CPU *cpuToUse = FindAvailableCPU(cpus);

        if (cpuToUse != NULL) {
            Task *shortestTask = FindTaskWithShortestWork(queue);

            // Set the task to the CPU
            cpuToUse->SetTaskInUse(shortestTask);
            cpuToUse->SetIdle(false);

            // Remove task from queue
            RemoveTaskFromVector(shortestTask->GetID(), queue);

            printf("Task sent to CPU.");
        } else {
            for (int j = 0; j < queue.size(); ++j) {
                queue[j].SetWaitTime(queue[j].GetWaitTime() + 1);
            }
        }

        // Decrement progress for all CPUs
        unsigned long cpuSize = cpus.size();

        for (int j = 0; j < cpuSize; ++j) {

            CPU cpu = cpus[j];

            if (!cpu.GetIdle() && cpu.GetProgress() > 0) {
                cpu.DecrementProgress();
            }

            if (cpu.GetProgress() <= 0) {
                // Task is done
                Task *t = cpu.GetTaskInUse();
                cpu.SetIdle(true);
                cpu.SetTaskInUse(nullptr);
                printf("Task is done, sending to output device.");

                // Send to output device
                outputQueue.push_back(*t);
                pQueueMax++;
            }
        }

        unsigned long outputSize = outputQueue.size();

        for (int k = 0; k < outputSize; ++k) {
            OutputDevice *od = FindAvailableOutputDevice(outputDevices);

            if (od != NULL) {
                od->SetIdle(false);
                od->SetTaskInUse(&(outputQueue[k]));

                waitTimes.push_back(outputQueue[k].GetWaitTime());

                // Remove task from queue
                RemoveTaskFromVector(outputQueue[k].GetID(), outputQueue);
            } else {
                for (int j = 0; j < outputQueue.size(); ++j) {
                    outputQueue[j].SetWaitTime(outputQueue[j].GetWaitTime() + 1);
                }

            }
        }

        unsigned long outputDeviceSize = outputDevices.size();

        for (int l = 0; l < outputDeviceSize; ++l) {

            OutputDevice device = outputDevices[l];

            if (!device.GetIdle()) {
                device.DecrementProgress();

                if (device.GetProgress() <= device.GetQuantum()) {
                    device.SetIdle(true);
                    device.SetTaskInUse(nullptr);

                    printf("Task is done.");
                }
            }
        }

        i++;
    }

    maxLengthQueue = queueMax;
    maxLengthOutputQueue = pQueueMax;
    idOfCPUGreatest = GetIdOfEntityHighestWork(cpus);
    idOfOutputGreatest = GetIdOfEntityHighestWork(outputDevices);
    averageWaitTime = CalculateAverageWaitTime(waitTimes);
    longestWaitTime = *max_element(waitTimes.begin(), waitTimes.end());


    return maxLengthQueue + "\n" +
           maxLengthOutputQueue + "\n" +
           idOfCPUGreatest + "\n" +
           idOfOutputGreatest + "\n" +
           averageWaitTime + "\n" +
           longestWaitTime + "\n" +
           averageTime;
}

void CreateOutput(string path, string result) {
    ofstream out(path);
    out << result;
    out.close();
}

double CalculateAverageWaitTime(vector<int> waitTimes) {
    int temp = 0;

    for (int i = 0; i < waitTimes.size(); ++i) {
        temp += waitTimes[i];
    }

    return temp / (double) waitTimes.size();
}


Task *FindTaskWithShortestWork(vector<Task> &queue) {
    unsigned long queueSize = queue.size();

    double work = -1;
    Task *task = nullptr;
    for (int i = 0; i < queueSize; ++i) {
        double qWork = queue[i].GetCPUWork();

        if (work < 0) {
            work = qWork;
            task = &queue[i];
        } else {
            if (qWork < work) {
                work = qWork;
                task = &queue[i];
            }
        }
    }

    return task;
}

template<class T>
int GetIdOfEntityHighestWork(vector<T> entities) {
    unsigned long queueSize = entities.size();

    double work = -1;
    T *t = nullptr;
    for (int i = 0; i < queueSize; ++i) {
        double qWork = entities[i].GetActiveTime();

        if (work < 0) {
            work = qWork;
            t = &entities[i];
        } else {
            if (qWork > work) {
                work = qWork;
                t = &entities[i];
            }
        }
    }

    return t->GetID();
}


// Find an idle CPU
CPU *FindAvailableCPU(vector<CPU> &cpus) {

    unsigned long cpuSize = cpus.size();

    for (int j = 0; j < cpuSize; ++j) {
        if (cpus[j].GetIdle()) {
            return &cpus[j];
        }
    }

    return NULL;
}

// Find an idle output device
OutputDevice *FindAvailableOutputDevice(vector<OutputDevice> &devices) {

    unsigned long deviceSize = devices.size();

    for (int j = 0; j < deviceSize; ++j) {
        if (devices[j].GetIdle()) {
            return &devices[j];
        }
    }

    return NULL;
}

Task *GetTaskByArrivalTime(double i, vector<Task> tasks) {
    for (int j = 0; j < tasks.size(); ++j) {
        if (tasks[i].GetArrivalTime() == i) {
            return &tasks[i];
        }
    }

    return NULL;
}

// Parse the input as specified in the DES spec
vector<string> ParseInput(string inputPath) {
    vector<string> lines;
    ifstream input(inputPath);

    for (string line; getline(input, line);) {
        lines.push_back(line);
    }

    return lines;
}

// Create CPU's according to the input
vector<CPU> CreateCPUs(vector<string> lines) {
    // In the first line: An integer N (Number of CPUs)
    // Next N lines contain doubles that represent frequency of the each CPU. (For a task, time
    // to spend in the CPU can be calculated as: CPU work of task / frequency of CPU )
    return CreateEntityVector<CPU>(lines);
}

// Create output devices according to the input
vector<OutputDevice> CreateOutputDevices(vector<string> lines) {
    // Next line contains an integer, the number of output devices units (M)
    // Next M lines contain a double, quantum value of each output unit
    return CreateEntityVector<OutputDevice>(lines);
}

// Create tasks according to the input
vector<Task> CreateTasks(vector<string> lines) {
    vector<Task> entities;

    // Next line contains an integer, the number of tasks to process
    int amount = stoi(lines[0]);

    // Remaining lines contain 3 doubles, arrival time, CPU work and output device work of
    // the task.
    for (int i = 0; i < amount; ++i) {
        // Split line into 3 doubles
        vector<string> elems = SplitString(lines[i + 1], ' ');
        Task entity = Task(stod(elems[0]), stod(elems[1]), stod(elems[2]), i);
        entities.push_back(entity);
    }

    return entities;
}

vector<string> SplitString(string main, char sep) {
    vector<string> result;
    string elem = "";

    for (int i = 0; i <= main.size(); ++i) {

        if (main[i] == sep || i == main.size()) {
            result.push_back(elem);
            elem = "";
        } else {
            elem += main[i];
        }
    }

    return result;
}

template<class T>
vector<T> CreateEntityVector(vector<string> lines) {
    vector<T> entities;

    int amount = stoi(lines[0]);

    for (int i = 0; i < amount; ++i) {
        T entity = T(stod(lines[i + 1]), i);
        entities.push_back(entity);
    }

    return entities;
}

// Remove task from a vector by its id
void RemoveTaskFromVector(double id, vector<Task> &vec) {

    double size = vec.size();

    for (int i = 0; i < size; ++i) {
        if (vec[i].GetID() == id) {
            vec.erase(vec.begin() + i);
            return;
        }
    }
}
