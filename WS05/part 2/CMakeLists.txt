cmake_minimum_required(VERSION 3.27)
project(part_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(part_2
        Book.cpp
        Book.h
        w5_p2.cpp
        Movie.cpp
        Movie.h
        SpellChecker.cpp
        SpellChecker.h
        Collection.h)
