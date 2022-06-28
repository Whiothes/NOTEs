cmake_minimum_required(VERSION  2.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(CTAP)

set(PROJECT_SOURCE_DIR      ${CMAKE_CURRENT_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(ch1)
add_subdirectory(ch5)
