//
// Created by Umut Seven on 19.05.2017.
//

#include "OutputDevice.h"

OutputDevice::OutputDevice(double q, int id) {
    this->quantum = q;
    this->idle = true;
    this->id = id;
}


double OutputDevice::GetQuantum() {
    return this->quantum;
}

