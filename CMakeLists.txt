cmake_minimum_required(VERSION 3.2)
project(core8)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/module")
set(EXTERNALS_PROJECTS_DIR externals)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

include(AddCatch)
include_directories(${CATCH_INCLUDE_DIR})

include_directories(include)
include_directories(include/core8)

file(GLOB sources src/*.cpp include/*.hpp include/core/*.hpp)

add_library(core8 SHARED ${sources})
set_target_properties(core8 PROPERTIES LINKER_LANGUAGE CXX)

enable_testing(true)
add_subdirectory(test)