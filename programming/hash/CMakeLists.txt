cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(hash)

add_library(hash
STATIC
member.h
member.c
chain_hash.h
chain_hash.c
open_hash.h
open_hash.c
)

add_executable(chain_hash_test chain_hash_test.c)
add_executable(open_hash_test open_hash_test.c)

target_link_libraries(chain_hash_test hash)
target_link_libraries(open_hash_test hash)
