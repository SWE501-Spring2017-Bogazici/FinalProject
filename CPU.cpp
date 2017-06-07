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

