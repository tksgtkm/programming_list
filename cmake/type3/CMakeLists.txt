cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(hello_library)

add_library(hello_library STATIC
src/hello.cc
)

target_include_directories(hello_library PUBLIC
${PROJECT_SOURCE_DIR}/include
)

add_executable(hello_binary src/main.cc)

target_link_libraries(hello_binary
PRIVATE
hello_library)
