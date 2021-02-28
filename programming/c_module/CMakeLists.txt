cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(module_project)

add_library(module_project
STATIC
ia.h
ia.c)

add_executable(hist hist.c)

target_link_libraries(hist module_project)
