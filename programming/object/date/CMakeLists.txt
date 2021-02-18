cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(oop_project)

add_library(oop_project
STATIC
date.h
date.cc)

add_executable(date date.cc)

target_link_libraries(date oop_project)
