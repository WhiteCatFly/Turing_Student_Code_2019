cmake_minimum_required(VERSION 3.0)
project(crawler CXX)

include_directories(
  ${PROJECT_SOURCE_DIR}/src
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_subdirectory(src)
add_subdirectory(src/htmlparser)
