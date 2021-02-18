cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(test)

set(SOURCES
../date.h
../date.cc)

add_library(source ${SOURCES})

add_executable(date_test date_test.cc)

target_link_libraries(date_test source)
