project(test)

add_executable(${PROJECT_NAME} account_test.cc)

target_link_libraries(${PROJECT_NAME}
sub::date
sub::accounting)
