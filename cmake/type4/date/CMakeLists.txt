project(date)

add_library(${PROJECT_NAME} date.cc)
add_library(sub::date ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
