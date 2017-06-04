cmake_minimum_required(VERSION 3.7)
project(project)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        easylogging++.h
        easylogging++.cc
        Cpu.cpp
        Cpu.h
        DES.cpp
        Event.cpp
        Event.h
        OutputDevice.cpp
        OutputDevice.h
        Simulation.cpp
        Simulation.h
        Task.cpp
        Task.h TaskCpuArrivalEvent.cpp TaskCpuArrivalEvent.h CpuInEvent.cpp CpuInEvent.h CpuOutEvent.cpp CpuOutEvent.h TaskOutArrivalEvent.cpp TaskOutArrivalEvent.h OutInEvent.cpp OutInEvent.h OutFreeEvent.cpp OutFreeEvent.h SJFComparator.cpp SJFComparator.h RRComparator.cpp RRComparator.h EventComparator.cpp EventComparator.h)

add_executable(project ${SOURCE_FILES})