cmake_minimum_required(VERSION 3.5)
project(AAPP_Project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package( Boost 1.67.0 COMPONENTS filesystem system )


if(Boost_FOUND)
include_directories(${Boost_INCLUDE_DIRS})
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
target_link_libraries(Project ${Boost_LIBRARIES})
endif()