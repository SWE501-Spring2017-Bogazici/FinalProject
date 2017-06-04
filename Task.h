//
// Created by Umut Seven on 19.05.2017.
//

#ifndef DES_TASK_H
#define DES_TASK_H


class Task {
private:
    double arrivalTime;
    double cpuWork;
    double outputWork;
    Task* taskInUse;
public:
    Task(double arrivalTime, double cpuWork, double outputWork);
    double GetArrivalTime();
    double GetCPUWork();
    double GetOutputWork();
};


#endif //DES_TASK_H
