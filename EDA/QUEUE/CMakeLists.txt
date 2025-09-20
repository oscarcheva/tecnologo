cmake_minimum_required(VERSION 3.31)
project(QUEUE)

set(CMAKE_CXX_STANDARD 20)

add_executable(QUEUE main.cpp
        queue.h
        queue.cpp)
