
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(accounting)

add_library(accounting
STATIC
accounting.h
accounting.cc
)

add_executable(main main.cc)

target_link_libraries(main accounting)
