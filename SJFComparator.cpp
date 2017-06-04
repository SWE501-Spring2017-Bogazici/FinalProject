//
// Created by Can Candan on 04/06/17.
//

#include "SJFComparator.h"
#include "easylogging++.h"

bool SJFComparator::operator()(const Task* lhs, const Task* rhs)
{
    return lhs->cpuWork > rhs->cpuWork;
}