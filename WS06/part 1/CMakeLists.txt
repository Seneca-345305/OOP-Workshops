cmake_minimum_required(VERSION 3.27)
project(part_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(part_1
        college_clean.txt
        Person.h
        w6_p1.cpp
        Employee.h
        Employee.cpp
        Utilities.cpp
        College.cpp)
