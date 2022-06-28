cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c11 -g)
set(EXECUTABLE_OUTPUT_PATH bin)

add_executable(msg msg)
add_executable(bug bug)
add_executable(pragma pragma)
add_executable(fibonacci fibonacci)
