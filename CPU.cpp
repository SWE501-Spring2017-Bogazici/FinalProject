//
// Created by Umut Seven on 19.05.2017.
//

#include "CPU.h"

CPU::CPU(double freq) {
    this->frequency = freq;
    this->idle = true;
    this->taskInUse = nullptr;
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
}

double CPU::GetProgress() {
    return this->progress;
}
