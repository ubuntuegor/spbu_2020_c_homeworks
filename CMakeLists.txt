cmake_minimum_required(VERSION 3.13)
project(spbu_2020_c_homeworks C)

set(CMAKE_C_STANDARD 11)

add_library(numericOperations library/numeric/operations.c)
add_library(ioInteger library/io/integer.c)

add_executable(task1_1 homework1/task1.c)
add_executable(task1_2 homework1/task2.c)
target_link_libraries(task1_2 numericOperations)
add_executable(task1_3 homework1/task3.c)
add_executable(task1_4 homework1/task4.c)
add_executable(task1_5 homework1/task5.c)

add_executable(task2_5 homework2/task5.c)
target_link_libraries(task2_5 ioInteger)
