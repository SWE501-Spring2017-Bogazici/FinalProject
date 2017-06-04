//
// Created by Umut Seven on 19.05.2017.
//

#include "OutputDevice.h"

OutputDevice::OutputDevice(double q, int id) {
    this->quantum = q;
    this->idle = true;
    this->id = id;
}

void OutputDevice::SetIdle(bool idle) {
    this->idle = idle;
}

bool OutputDevice::GetIdle() {
    return this->idle;
}

Task *OutputDevice::GetTaskInUse() {
    return this->taskInUse;
}

void OutputDevice::SetTaskInUse(Task *task) {
    this->taskInUse = task;
    this->progress = task->GetOutputWork();
}


void OutputDevice::DecrementProgress() {
    this->progress-= progress;
    this->activeTime += 1;
}

double OutputDevice::GetQuantum() {
    return this->quantum;
}

double OutputDevice::GetProgress() {
    return this->progress;
}

double OutputDevice::GetActiveTime() {
    return this->activeTime;
}

double OutputDevice::GetID() {
    return this->id;
}
