cmake_minimum_required(VERSION 3.31)
project(TADS C)

set(CMAKE_C_STANDARD 11)

add_executable(TADS main.c
        punto.c
        punto.h)
