cmake_minimum_required(VERSION 3.6)
project(DES)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp CPU.cpp CPU.h OutputDevice.cpp OutputDevice.h Task.cpp Task.h SimulationEntity.cpp SimulationEntity.h)
add_executable(DES ${SOURCE_FILES})