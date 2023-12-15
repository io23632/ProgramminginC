cmake_minimum_required(VERSION 3.26)
project(Minseweeper C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Minseweeper
        drv.c
        ms.c
        ms.h
        ms_2.c
        re_write.c)
