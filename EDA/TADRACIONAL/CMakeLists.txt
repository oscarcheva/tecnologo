cmake_minimum_required(VERSION 3.31)
project(TADRACIONAL C)

set(CMAKE_C_STANDARD 11)

add_executable(TADRACIONAL main.c
        racional.h
        racional.c)
