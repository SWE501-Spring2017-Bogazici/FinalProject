//
// Created by Umut Seven on 19.05.2017.
//

#include "CPU.h"

CPU::CPU(double freq) {
    this->frequency = freq;
    this->idle = true;
}

bool CPU::GetIdle() {
    return this->idle;
}