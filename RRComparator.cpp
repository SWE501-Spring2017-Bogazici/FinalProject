//
// Created by Can Candan on 04/06/17.
//

#include "RRComparator.h"
#include "easylogging++.h"

bool RRComparator::operator()(const Task* lhs, const Task* rhs)
{
    return lhs->outtime > rhs->outtime;
}