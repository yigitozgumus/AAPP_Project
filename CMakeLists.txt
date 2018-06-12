cmake_minimum_required(VERSION 3.5)
project(AAPP_Project)

set(CMAKE_CXX_STANDARD 11)

include_directories(header)

add_executable(Project
        header/graphcomponent.h
        header/typedef.h
        header/tarjan.h
        header/nuutila.h
        header/pearce.h
        src/tarjan.cpp
        src/pearce.cpp
        src/nuutila.cpp
        src/analyzer.cpp
        src/experiment.cpp
        src/graphcomponent.cpp
        src/main.cpp)
