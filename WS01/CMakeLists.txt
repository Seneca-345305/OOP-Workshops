cmake_minimum_required(VERSION 3.27)
project(WS01)

set(CMAKE_CXX_STANDARD 14)

include_directories("part 2")

add_executable(WS01
        "part 2/event.cpp"
        "part 2/event.h"
        "part 2/monday.txt"
        "part 2/tuesday.txt"
        "part 2/w1_p2.cpp")
