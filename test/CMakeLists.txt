cmake_minimum_required(VERSION 3.8)

add_executable(shell4cpp_test shell_test.cpp)

target_include_directories(shell4cpp_test PRIVATE shell4cpp)

target_link_libraries(shell4cpp_test shell4cpp)
# add_test(shell4cpp_test)
