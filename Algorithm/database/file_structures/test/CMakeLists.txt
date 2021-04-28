cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(test)

set(SOURCES
pearson.h
pearson.cc)

add_library(source ${SOURCES})

add_executable(write_str write_str.cc)
add_executable(read_del read_del.cc)

target_link_libraries(write_str source)
target_link_libraries(read_del source)
