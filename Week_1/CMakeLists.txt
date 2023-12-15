cmake_minimum_required(VERSION 3.26)
project(Week_1 C)

set(CMAKE_C_STANDARD 99)

add_library(Week_1 Calculate_Rectangle_area.c
        Char.c
        Exercises/Hello_World/twice_the_sum.c
        Exercises/Hello_World/twice_the_sum.c)
add_executable(new_target Exercises/Hello_World/twice_the_sum.c
        Exercises/Hello_World/Letter_C.c)
