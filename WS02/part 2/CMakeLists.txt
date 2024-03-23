cmake_minimum_required(VERSION 3.27)
project(WS02)

set(CMAKE_CXX_STANDARD 17)

include_directories(".")

add_executable(WS02
        "StringSet.cpp"
        "StringSet.h"
        "TimedEvents.cpp"
        "TimedEvents.h"
        "w2_p2.cpp"
        "TimedEvents.cpp"
)
