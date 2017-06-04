//
// Created by Umut Seven on 19.05.2017.
//

#include "CPU.h"

CPU::CPU(double freq, int id) {
    this->frequency = freq;
    this->idle = true;
    this->taskInUse = nullptr;
    this->id = id;
}

bool CPU::GetIdle() {
    return this->idle;
}

Task *CPU::GetTaskInUse() {
    return this->taskInUse;
}

void CPU::SetTaskInUse(Task *task) {
    this->progress = task->GetCPUWork() / this->frequency;
    this->taskInUse = task;
}

void CPU::SetIdle(bool idle) {
    this->idle = idle;
}

void CPU::DecrementProgress() {
    this->progress-= progress;
    this->activeTime+= 1;
}

double CPU::GetProgress() {
    return this->progress;
}

double CPU::GetActiveTime() {
    return this->activeTime;
}

double CPU::GetID() {
    return this->id;
}
