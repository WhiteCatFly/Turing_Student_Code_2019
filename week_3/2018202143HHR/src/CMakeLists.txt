cmake_minimum_required(VERSION 3.0)
project(crawler CXX)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "8")
    message(FATAL_ERROR "Insufficient gcc version")
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "6")
    message(FATAL_ERROR "Insufficient clang version")
  endif()
endif()

set(CMAKE_CXX_FLAGS "-Wall -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC "*.cc")
add_executable(crawler ${SRC})
target_link_libraries(crawler stdc++fs)
