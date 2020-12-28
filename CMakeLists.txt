cmake_minimum_required(VERSION 3.13)
project(spbu_2020_c_homeworks C)

set(CMAKE_C_STANDARD 11)

add_library(numericOperations library/numeric/operations.c)
target_link_libraries(numericOperations PRIVATE m)
add_library(numericIO library/numeric/io.c)
add_library(numericList library/numeric/list.c)
add_library(numericStack library/numeric/stack.c)
add_library(numericBST library/numeric/binary_trees/bst.c
                       library/numeric/binary_trees/node_structures/bst_node.c
                       library/numeric/binary_trees/node_operations/basic_operations.c)
add_library(numericAVL library/numeric/binary_trees/avl.c
                       library/numeric/binary_trees/node_structures/avl_node.c
                       library/numeric/binary_trees/node_operations/basic_operations.c
                       library/numeric/binary_trees/node_operations/avl_balancing.c)
target_link_libraries(numericAVL numericOperations)
add_library(numericHashTable library/numeric/hash_table/hash_table.c
                             library/numeric/hash_table/default_hash_functions.c)

add_library(stringIO library/string/io.c)

add_library(graph library/graph/graph.c)

add_library(hashTable library/hash_table/hash_table.c
                      library/hash_table/default_hash_functions.c
                      library/hash_table/count_statistics.c)
target_link_libraries(hashTable stringIO numericOperations)

add_library(dfa library/dfa/dfa.c)

add_executable(task1_1 homework1/task1.c)
add_executable(task1_2 homework1/task2.c)
target_link_libraries(task1_2 numericOperations)
add_executable(task1_3 homework1/task3.c)
add_executable(task1_4 homework1/task4.c)
add_executable(task1_5 homework1/task5.c)

add_executable(task2_1 homework2/task1.c)
target_link_libraries(task2_1 numericOperations numericIO)
add_executable(task2_2 homework2/task2.c)
target_link_libraries(task2_2 numericOperations numericIO)
add_executable(task2_3 homework2/task3.c)
target_link_libraries(task2_3 numericIO)
add_executable(task2_4 homework2/task4.c)
target_link_libraries(task2_4 numericOperations numericIO)
add_executable(task2_5 homework2/task5.c)
target_link_libraries(task2_5 numericIO)

add_executable(task3_1 homework3/task1.c)
target_link_libraries(task3_1 numericList)
add_executable(task3_2 homework3/task2.c)
target_link_libraries(task3_2 numericIO numericList)

add_executable(task4_1 homework4/task1.c)
target_link_libraries(task4_1 numericStack stringIO)
add_executable(task4_2 homework4/task2.c)
target_link_libraries(task4_2 numericIO)
add_executable(task4_3 homework4/task3.c)
target_link_libraries(task4_3 numericIO)

add_executable(task5_1 homework5/task1.c)
target_link_libraries(task5_1 numericBST numericIO)
add_executable(task5_2 homework5/task2.c)
target_link_libraries(task5_2 numericAVL numericIO)
add_executable(trees_demo homework5/trees_demo.c)
target_link_libraries(trees_demo numericBST numericAVL numericIO)

add_executable(task6_1 homework6/task1.c)
target_link_libraries(task6_1 stringIO hashTable)

add_executable(task7_1 homework7/task1.c)
target_link_libraries(task7_1 graph)
add_executable(task7_2 homework7/task2.c)
target_link_libraries(task7_2 numericList graph)

add_executable(task8_1 homework8/task1.c)
target_link_libraries(task8_1 dfa stringIO)

add_executable(testing1_1 test1/task1.c)
target_link_libraries(testing1_1 numericIO)
add_executable(testing1_2_try1 test1/task2_try1.c)

add_executable(testing1_2_try2 test1/task2_try2.c test1/vector.c)
target_link_libraries(testing1_2_try2 numericIO m)

add_executable(testing2_1 test2/task1.c)
target_link_libraries(testing2_1 numericIO)
add_executable(testing2_2 test2/task2.c)
add_executable(testing2_3 test2/task3.c)
target_link_libraries(testing2_3 numericIO numericList)

add_executable(testing3_1 test3/task1.c)
target_link_libraries(testing3_1 numericIO numericHashTable)
add_executable(testing3_3 test3/task3.c)
target_link_libraries(testing3_3 dfa stringIO)
