cmake_minimum_required(VERSION 3.27)
project(WS03)

set(CMAKE_CXX_STANDARD 14)

include_directories("part 1")

add_executable(WS03
        "part 2/w3_p2.cpp"
        "part 2/Pair.cpp"
        "part 2/Set.h"
        #        "part 2/w3_p2.cpp"
)
