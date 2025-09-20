cmake_minimum_required(VERSION 3.31)
project(STACK)

set(CMAKE_CXX_STANDARD 20)

add_executable(STACK main.cpp
        stack.h
        stack.cpp)
