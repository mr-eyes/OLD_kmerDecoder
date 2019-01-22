# Minimum cmake version
cmake_minimum_required (VERSION 3.0.0)

project (inputModule C CXX)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++14 -fPIC -fopenmp -W -Wall -pedantic")

file(GLOB SOURCES "src/*.cpp" "main.cpp")

include_directories("include")

add_executable(inputModule ${SOURCES})