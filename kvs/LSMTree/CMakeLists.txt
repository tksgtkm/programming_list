cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(lsmtree)

add_library(lsmtree
STATIC
hash.h
hash.cc
bloom.h
disk_level.h
disk_run.h
run.h
skiplist.h
hashmap.h
lsm.h
)

add_executable(main main.cc)

target_link_libraries(main lsmtree)
