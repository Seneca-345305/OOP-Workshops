cmake_minimum_required(VERSION 3.27)
project(part_2)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(part_2
        College.cpp
        College.h
        Employee.cpp
        Employee.h
        Person.h
        Utilities.cpp
        Utilities.h
        w6_p2.cpp
        Student.h
        Student.cpp
        Professor.h
        Professor.cpp)
