#include <iostream>
#include <fstream>
#include <vector>
#include "CPU.h"
#include "OutputDevice.h"
#include "Task.h"

using namespace std;

vector<string> ParseInput(string inputPath);

vector<CPU> CreateCPUs(vector<string> lines);

vector<OutputDevice> CreateOutputDevices(vector<string> lines);

vector<Task> CreateTasks(vector<string> lines);

vector<string> SplitString(string main, char sep);

template<class T>
vector<T> CreateEntityVector(vector<string> lines);

void Simulate(vector<CPU> cpus, vector<Task> tasks, vector<OutputDevice> outputDevices);

Task *GetTaskByArrivalTime(double i, vector<Task> tasks);

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

    // Remove CPU lines from input vector
    lines.erase(lines.begin(), lines.begin() + cpus.size() + 1);

    vector<OutputDevice> outputDevices = CreateOutputDevices(lines);

    // Remove output device lines from input vector
    lines.erase(lines.begin(), lines.begin() + outputDevices.size() + 1);

    vector<Task> tasks = CreateTasks(lines);

    Simulate(cpus, tasks, outputDevices);
    return 0;
}

void Simulate(vector<CPU> cpus, vector<Task> tasks, vector<OutputDevice> outputDevices) {
    vector<Task> queue;

    // Time
    double i = 0;

    // Main event loop
    while (i <= MAX_TIME) {
        // Get task
        Task *task = GetTaskByArrivalTime(i, tasks);

        if (task == NULL) {
            // No tasks arrived, do nothing
        } else {
            queue.push_back(*task);
        }

        i++;
    }
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
        Task entity = Task(stod(elems[0]), stod(elems[1]), stod(elems[2]));
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
        T entity = T(stod(lines[i + 1]));
        entities.push_back(entity);
    }

    return entities;
}
