//
// Created by Can Candan on 04/06/17.
//

#ifndef SRC_SJFCOMPARATOR_H
#define SRC_SJFCOMPARATOR_H


#include "Task.h"

class SJFComparator {
public:
    bool operator()(const Task* lhs, const Task* rhs);
};


#endif //SRC_SJFCOMPARATOR_H
