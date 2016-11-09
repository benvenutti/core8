cmake_minimum_required(VERSION 3.2)
project(core8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

include_directories(include)
include_directories(include/core8)

file(GLOB sources src/*.cpp include/*.hpp include/core/*.hpp)

add_library(foo SHARED ${sources})
set_target_properties(foo PROPERTIES LINKER_LANGUAGE CXX)