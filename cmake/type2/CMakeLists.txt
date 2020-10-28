cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(hello_headers)

set(SOURCES
src/hello.cc
src/main.cc
)

add_executable(hello_headers ${SOURCES})

# ターゲットのビルドコマンドに含める必要があるディリクトリを指定する
target_include_directories(hello_headers
PRIVATE
${PROJECT_SOURCE_DIR}/include
)
