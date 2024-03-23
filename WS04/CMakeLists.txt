cmake_minimum_required(VERSION 3.27)
project(WS04)

set(CMAKE_CXX_STANDARD 14)

add_executable(WS04
        "part 2/data.txt"
        "part 2/w4_p2.cpp"
        "part 2/Toy.cpp"
        "part 2/Child.h"
        "part 2/Child.cpp"
        "part 1/Toy.h"
        "part 2/ConfirmOrder.cpp"
)
