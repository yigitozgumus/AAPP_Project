cmake_minimum_required(VERSION 2.8.4)

project(SCC)

set(Boost_USE_MULTITHREADED ON)
set(EXECUTABLE_OUTPUT_PATH "out")

find_package(Boost 1.67.0 COMPONENTS REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()

add_executable(graph graph.cpp)

if(Boost_FOUND)

    target_link_libraries(graph ${Boost_LIBRARIES})

endif()
