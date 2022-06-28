cmake_minimum_required(VERSION 3.0)

add_definitions(-std=c++11 -g)

project(leetcode)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(PROJECT_SOURCE_DIR      ${CMAKE_CURRENT_SOURCE_DIR})
SET(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH     ${PROJECT_SOURCE_DIR}/lib)



add_subdirectory(simple)
add_subdirectory(array)
