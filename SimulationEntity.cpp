//
// Created by Umut Seven on 07.06.2017.
//

#include "SimulationEntity.h"

double SimulationEntity::GetProgress() {
    return this->progress;
}

double SimulationEntity::GetActiveTime() {
    return this->activeTime;
}

double SimulationEntity::GetID() {
    return this->id;
}

void SimulationEntity::SetIdle(bool idle) {
    this->idle = idle;
}

bool SimulationEntity::GetIdle() {
    return this->idle;
}

Task *SimulationEntity::GetTaskInUse() {
    return this->taskInUse;
}

void SimulationEntity::SetTaskInUse(Task *task) {
    this->taskInUse = task;
    this->progress = task->GetOutputWork();
}


void SimulationEntity::DecrementProgress() {
    this->progress-= progress;
    this->activeTime += 1;
}

