cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(test)

set(SOURCES
int_array.h)

add_library(source ${SOURCES})

add_executable(int_array_test int_array_test.cc)

target_link_libraries(int_array_test source)
