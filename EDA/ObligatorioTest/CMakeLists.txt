cmake_minimum_required(VERSION 3.31)
project(ObligatorioTest)

set(CMAKE_CXX_STANDARD 20)

add_executable(ObligatorioTest main.cpp
        version.h
        version.cpp
        cadena.h
        cadena.cpp)
