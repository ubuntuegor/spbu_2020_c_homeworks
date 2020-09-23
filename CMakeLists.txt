cmake_minimum_required(VERSION 3.13)
project(spbu_2020_c_homeworks C)

set(CMAKE_C_STANDARD 11)

add_library(numericOperations library/numeric/operations.c)
add_library(numericList library/numeric/list.c)

add_executable(task1_1 homework1/task1.c)

add_executable(numericListTest tests/numericListTest.c)
target_link_libraries(numericListTest numericList)

add_executable(numericOperationsTest tests/numericOperationsTest.c)
target_link_libraries(numericOperationsTest numericOperations)
