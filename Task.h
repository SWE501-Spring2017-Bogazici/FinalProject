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
    double id;
    int waitTime;
    int startTime;
    int endTime;
public:
    Task(double arrivalTime, double cpuWork, double outputWork, double id);
    double GetArrivalTime();
    double GetCPUWork();
    double GetOutputWork();
    double GetID();
    void SetWaitTime(int waitTime);
    int GetWaitTime();
    void SetStartTime(int startTime);
    int GetStartTime();
    void SetEndTime(int endTime);
    int GetEndTime();

};


#endif //DES_TASK_H
