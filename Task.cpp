/*
 * Task.cpp
 *
 *  Created on: Jun 2, 2017
 *      Author: Can Candan
 */

#include "Task.h"

Task::Task() {
	// TODO Auto-generated constructor stub

}

Task::Task(double arrivalTime, double cpuWork, double outputWork) : arrivalTime(arrivalTime), cpuWork(cpuWork), outputWork(outputWork) {
    remainingOutWork=outputWork;
    finished=false;
}



Task::~Task() {
	// TODO Auto-generated destructor stub
}

double Task::getOutTime() const {
    return outTime;
}

void Task::setOutTime(double outTime) {
    Task::outTime = outTime;
}

double Task::getRemainingOutWork() const {
    return remainingOutWork;
}

void Task::setRemainingOutWork(double remainingOutWork) {
    Task::remainingOutWork = remainingOutWork;
}

bool Task::isFinished() const {
    return finished;
}

void Task::setFinished(bool finished) {
    Task::finished = finished;
}

double Task::outputWorked(double time, double quantum) {
    if (remainingOutWork <= quantum) {
        outTime = time + remainingOutWork;
        double worked=remainingOutWork;
        remainingOutWork=0;
        finished=true;
        return worked;
    } else {
        remainingOutWork=remainingOutWork-quantum;
        outTime=time+quantum;
        return quantum;
    }

}

double Task::getArrivalTime() const {
    return arrivalTime;
}

void Task::setArrivalTime(double arrivalTime) {
    Task::arrivalTime = arrivalTime;
}

double Task::getCpuWork() const {
    return cpuWork;
}

void Task::setCpuWork(double cpuWork) {
    Task::cpuWork = cpuWork;
}

double Task::getOutputWork() const {
    return outputWork;
}

void Task::setOutputWork(double outputWork) {
    Task::outputWork = outputWork;
}

double Task::getWaitCpu() const {
    return waitCpu;
}

void Task::setWaitCpu(double waitCpu) {
    Task::waitCpu = waitCpu;
}

double Task::getWaitOut() const {
    return waitOut;
}

void Task::setWaitOut(double waitOut) {
    Task::waitOut = waitOut;
}

double Task::getCpuServiceStopTime() const {
    return cpuServiceStopTime;
}

void Task::setCpuServiceStopTime(double cpuServiceStopTime) {
    Task::cpuServiceStopTime = cpuServiceStopTime;
}

int Task::getId() const {
    return id;
}

void Task::setId(int id) {
    Task::id = id;
}

