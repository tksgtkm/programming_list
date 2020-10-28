
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(intro LANGUAGES CXX)

add_library(interpliter
  STATIC
    util.h
    util.cc)

add_executable(main main.cc)

target_link_libraries(main interpliter)

