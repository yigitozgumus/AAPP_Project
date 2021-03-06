cmake_minimum_required(VERSION 3.9.3)
project(AAPP_Project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package( Boost COMPONENTS filesystem system )


if(Boost_FOUND)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(Project
header/graphcomponent.h
header/utilities.h
header/tarjan.h
header/nuutila.h
header/pearce.h
header/analyzer.h
header/visualize.h
header/application.h
src/cpp/application.cpp
src/cpp/visualize.cpp
src/cpp/tarjan.cpp
src/cpp/pearce.cpp
src/cpp/nuutila.cpp
src/cpp/analyzer.cpp
src/cpp/graphcomponent.cpp
src/cpp/main.cpp)
target_link_libraries(Project ${Boost_LIBRARIES})
endif()