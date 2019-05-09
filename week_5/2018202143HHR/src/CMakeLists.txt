cmake_minimum_required(VERSION 3.0)
project(big-integer CXX)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC "*.cc")
add_executable(big-integer ${SRC})
target_link_libraries(big-integer stdc++fs)
