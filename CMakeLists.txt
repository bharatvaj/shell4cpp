cmake_minimum_required(VERSION 3.8)

project(shell4cpp VERSION 0.1.0 LANGUAGES CXX)

add_library(shell4cpp INTERFACE)


target_include_directories(shell4cpp INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

add_subdirectory(test)
