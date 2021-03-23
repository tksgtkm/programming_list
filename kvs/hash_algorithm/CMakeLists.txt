cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(hash_data)

add_library(hash_data
STATIC
hash.h
hash.c
linked_lists.h
linked_lists.c
chained_hash.h
chained_hash.c
)

add_executable(hash_test hash_test.c)
add_executable(linked_lists_test linked_lists_test.c)
add_executable(chained_hash_test chained_hash_test.c)

target_link_libraries(hash_test hash_data)
target_link_libraries(linked_lists_test hash_data)
target_link_libraries(chained_hash_test hash_data)
