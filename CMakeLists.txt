cmake_minimum_required(VERSION 3.13)
project(spbu_2020_c_homeworks C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB
    library/commonUtils/numericOperations.c
    library/commonUtils/numericList.c
)
add_library(library ${SOURCE_LIB})

add_executable(task1_1 homework1/task1.c)

add_executable(numericListTest tests/numericListTest.c)
target_link_libraries(numericListTest library)
