cmake_minimum_required(VERSION 3.31)
project(TREES)

set(CMAKE_CXX_STANDARD 20)

add_executable(TREES main.cpp
        binary.h
        bsearch.h
        general.h
        binary.cpp
        bsearch.cpp
        general.cpp)
