//============================================================================
// Name        : DES.cpp
// Author      : Can Candan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "Cpu.h"
#include "Event.h"
#include "Simulation.h"

#include "easylogging++.h"


INITIALIZE_EASYLOGGINGPP

using namespace std;


void readInputFile(string inputFileName) {

}

int main(int argc, char *argv[]) {

    el::Configurations defaultConf;
    defaultConf.setToDefault();
    defaultConf.set(el::Level::Global, el::ConfigurationType::Enabled, "false");
    el::Loggers::reconfigureLogger("default", defaultConf);


    if ( argc != 3 ) {
        cout << "usage: " << argv[0] << " inputFile outputFile\n";
    } else {
        Simulation *sim = new Simulation();

        ifstream inputFile(argv[1]);


        int numCpus;
        inputFile >> numCpus;


        for (int i = 0; i < numCpus; i++) {
            int freq;
            inputFile >> freq;
            Cpu *cpu = new Cpu(i + 1, freq);
            sim->addCpu(cpu);
        }

        int numOuts;
        inputFile >> numOuts;

        for (int i = 0; i < numOuts; i++) {
            int quantum;
            inputFile >> quantum;
            OutputDevice *out = new OutputDevice(i + 1, quantum);
            sim->addOutputDevice(out);
        }

        int numTasks;
        inputFile >> numTasks;

        for (int i = 0; i < numTasks; i++) {
            double arrTime, cpuWork, outWork;
            inputFile >> arrTime >> cpuWork >> outWork;
            Task *t = new Task(arrTime, cpuWork, outWork);
            sim->addTask(t);
        }

        sim->run();

        ofstream outputFile;
        outputFile.open(argv[2]);

        outputFile << sim->sjf_queue_max_size << endl;
        outputFile << sim->rr_queue_max_size << endl;
        outputFile << sim->max_active_cpu_id << endl;
        outputFile << sim->max_active_out_id << endl;
        outputFile << sim->average_wait_time << endl;
        outputFile << sim->longest_wait_time << endl;
        outputFile << sim->average_time_spent << endl;

        outputFile.close();
    }



	return 0;
}
