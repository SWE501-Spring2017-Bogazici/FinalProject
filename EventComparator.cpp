//
// Created by Can Candan on 04/06/17.
//

#include "EventComparator.h"
#include "Event.h"
#include "easylogging++.h"

bool EventComparator::operator() (const Event* a, const Event* b) {
    return a->getTime()> b->getTime();
}