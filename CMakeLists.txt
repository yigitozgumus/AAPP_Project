cmake_minimum_required(VERSION 3.10)
project(SCC)

set(CMAKE_CXX_STANDARD 11)

include_directories(header)

add_executable(SCC
        header/algorithms.h
        header/graphcomponent.h
        header/typedef.h
        src/algorithms.cpp
        src/analyzer.cpp
        src/experiment.cpp
        src/graphcomponent.cpp
        src/main.cpp)
