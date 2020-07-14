cmake_minimum_required(VERSION 3.16)

set(DESPAT_PROJECT_NAME design_patterns_cpp)
project(${DESPAT_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

# Source files
file(GLOB_RECURSE SRCS src/**.cpp)

# 3rd Party libraries include
include_directories(externals/third_party/googletest/googlemock/include)
include_directories(externals/third_party/googletest/googletest/include)

# Project's directory
include_directories(src)

add_executable(${DESPAT_PROJECT_NAME} ${SRCS})

# Add target build dependency to gtest and gmock
add_dependencies(${DESPAT_PROJECT_NAME} gtest gmock)

# Link project with gtest and gmock
target_link_libraries(${DESPAT_PROJECT_NAME} PUBLIC gtest gmock)

add_subdirectory(externals/third_party/googletest)