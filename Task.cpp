//
// Created by Umut Seven on 19.05.2017.
//

#include "Task.h"

Task::Task(double _arrivalTime, double _cpuWork, double _outputWork, double _id) {
    this->arrivalTime = _arrivalTime;
    this->cpuWork = _cpuWork;
    this->outputWork = _outputWork;
    this->id = _id;
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

double Task::GetID() {
    return this->id;
}

int Task::GetWaitTime() {
    return this->waitTime;
}

void Task::SetWaitTime(int _waitTime) {
    this->waitTime = _waitTime;
}

void Task::SetEndTime(int endTime) {
    this->endTime = endTime;
}

int Task::GetEndTime() {
    return this->endTime;
}

int Task::GetStartTime() {
    return this->startTime;
}

void Task::SetStartTime(int startTime) {
    this->startTime = startTime;
}

