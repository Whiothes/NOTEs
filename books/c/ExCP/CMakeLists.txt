cmake_minimum_required(VERSION 2.8)

# definition options
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -std=gnu11")
if (APPLE)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_DARWIN_C_SOURCE")
elseif(UNIX)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_POSIX_C_SOURCE=200809L -D_GNU_SOURCE")
endif()


project(ExCP)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(PROJECT_SOURCE_DIR      ${CMAKE_CURRENT_SOURCE_DIR})
SET(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH     ${PROJECT_SOURCE_DIR}/lib)


add_subdirectory(ch1)
add_subdirectory(ch3)
add_subdirectory(ch6)
add_subdirectory(ch7)
add_subdirectory(ch8)
