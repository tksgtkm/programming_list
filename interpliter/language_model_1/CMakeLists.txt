
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project (owl_project)

add_library(owl_sub
  SHARED
    source.h
    gettoken.h
    util.h
    interpret.h
    source.cc
    gettoken.cc
    util.cc
    interpret.cc
)

add_executable(owl_lang main.cc)

target_link_libraries(owl_lang owl_sub)
