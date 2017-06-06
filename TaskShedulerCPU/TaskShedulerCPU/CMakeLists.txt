cmake_minimum_required(VERSION 3.6)
project(FinalProject)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES TaskShedulerCPU.cpp Task.cpp Task.h stdafx.cpp stdafx.h targetver.h)
add_executable(FinalProject ${SOURCE_FILES})