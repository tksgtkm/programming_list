cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(index)

add_library(index
STATIC
stack.h
stack.c
# spla_tree.h
# spla_tree.c
# segment_tree.h
# segment_tree.c
array_heap.h
array_heap.c
)

add_executable(stack_test stack_test.c)
# add_executable(spla_test spla_tree_test.c)
# add_executable(memory_allocation memory_allocation.c)
add_executable(memory_segment memory_segment.c)
add_executable(file_io file_io.c)
# add_executable(segment_test segment_tree_test.c)
add_executable(array_heap_test array_heap_test.c)

target_link_libraries(stack_test index)
# target_link_libraries(spla_test index)
# target_link_libraries(segment_test index)
target_link_libraries(array_heap_test index)
