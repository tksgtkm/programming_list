cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(marsdb)

add_library(marsdb
SHARED
array_mng.h
array_mng.cc
array_itr.h
array_itr.cc
array_ctrl.h
array_ctrl.cc
)

add_executable(array_ctrl_test array_ctrl_test.cc)

target_link_libraries(array_ctrl_test marsdb)
