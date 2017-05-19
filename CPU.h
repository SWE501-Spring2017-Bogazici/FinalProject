//
// Created by Umut Seven on 19.05.2017.
//

#ifndef DES_CPU_H
#define DES_CPU_H


class CPU {
private:
    double frequency;
    bool idle;
public:
    CPU(double frequency);
    bool GetIdle();
};


#endif //DES_CPU_H
