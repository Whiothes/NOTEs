cmake_minimum_required(VERSION 2.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(PROJECT_SOURCE_DIR ".")
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(ch1)


add_custom_target(cp ALL
  cp "${PROJECT_SOURCE_DIR}/compile_commands.json" ../
  )
