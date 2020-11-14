
cmake_minimum_required(VERSION 3.14)

project (owl_lang)

add_library(owl_sub
  SHARED
    util.h
    util.cc
    gettoken.h
    gettoken.cc
    interpret.h
    interpret.cc
    source.h
    source.cc
)

add_executable(owl_lang main.cc)

target_link_libraries(owl_lang owl_sub)
