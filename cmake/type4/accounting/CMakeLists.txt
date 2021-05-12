project(accounting)

add_library(${PROJECT_NAME} accounting.cc)
add_library(sub::accounting ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
