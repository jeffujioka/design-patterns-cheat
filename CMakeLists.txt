cmake_minimum_required(VERSION 3.16)

set(DESPAT_PROJECT_NAME design_patterns_cpp)
project(${DESPAT_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

set(BOOST_ROOT "3rd-party/boost_1_73_0")

find_package(Boost 1.73.0)

if (Boost_FOUND)
    message(STATUS "Found Boost module")
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(STATUS "Boost module NOT found!")
endif()

# Source files
file(GLOB_RECURSE SRCS src/**.cpp)

# 3rd Party libraries include
include_directories(externals/third_party/googletest/googlemock/include)
include_directories(externals/third_party/googletest/googletest/include)

# Project's directory
include_directories(src)

add_executable(${DESPAT_PROJECT_NAME} ${SRCS} src/bridge/Pimpl.h src/bridge/Person.cpp src/bridge/Person.h src/bridge/Person_Test.cpp src/bridge/ShapeRenderer.h src/bridge/ShapeRenderer_Test.cpp src/singleton/SingletonDB.h src/singleton/SingletonDB_Test.cpp src/decorator/ShapeDecorator.h src/decorator/DynamicShapeDecorator_Test.cpp)

# Add target build dependency to gtest and gmock
add_dependencies(${DESPAT_PROJECT_NAME} gtest gmock)

# Link project with gtest and gmock
target_link_libraries(${DESPAT_PROJECT_NAME} PUBLIC gtest gmock)

add_subdirectory(externals/third_party/googletest)