cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(stack_project LANGUAGES C CXX)

set(SOURCES
bc_stack.h
array_stack.h
array_stack.cc
lnk_stack.h
lnk_stack.cc)

add_library(source ${SOURCES})

add_executable(array_stack_test array_stack_test.cc)
add_executable(lnk_stack_test lnk_stack_test.cc)

target_link_libraries(array_stack_test source)
target_link_libraries(lnk_stack_test source)

# project(App)
# set(CMAKE_CXX_STANDARD 17)
# add_executable(App array_stack.cc bc_stack.h array_stack.h)
