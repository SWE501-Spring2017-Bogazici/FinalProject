//
// Created by Can Candan on 04/06/17.
//

#ifndef SRC_EVENTCOMPARATOR_H
#define SRC_EVENTCOMPARATOR_H




class Event;

class EventComparator {
public:
    bool operator() (const Event* a, const Event* b);
};


#endif //SRC_EVENTCOMPARATOR_H
