cmake_minimum_required(VERSION 3.16)
project(design_patterns_cpp)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRCS src/**.cpp)

add_executable(design_patterns_cpp ${SRCS})