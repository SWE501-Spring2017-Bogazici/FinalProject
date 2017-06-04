//
// Created by Umut Seven on 19.05.2017.
//

#include "Task.h"

Task::Task(double _arrivalTime, double _cpuWork, double _outputWork) {
    this->arrivalTime = _arrivalTime;
    this->cpuWork = _cpuWork;
    this->outputWork = _outputWork;
}

double Task::GetArrivalTime() {
    return this->arrivalTime;
}

double Task::GetCPUWork() {
    return this->cpuWork;
}

double Task::GetOutputWork() {
    return this->outputWork;
}

