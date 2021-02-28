cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(db_lib)

add_library(db_lib
STATIC
btree.h
btree.c)

add_executable(main main.c)

target_link_libraries(main db_lib)
