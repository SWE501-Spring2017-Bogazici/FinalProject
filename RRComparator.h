//
// Created by Can Candan on 04/06/17.
//

#ifndef SRC_RRCOMPARATOR_H
#define SRC_RRCOMPARATOR_H


#include "Task.h"

class RRComparator {
public:
    bool operator()(const Task* lhs, const Task* rhs);
};


#endif //SRC_RRCOMPARATOR_H
