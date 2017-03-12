cmake_minimum_required(VERSION 3.2)
project(core8)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/module")
set(EXTERNALS_PROJECTS_DIR externals)

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

# compiler variables
set(CPP_DIALECT "-std=c++14")
set(FLAGS "-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -pedantic-errors")
set(FLAGS "${FLAGS} -Wunused -Wold-style-cast -Wsign-conversion")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS} ${CPP_DIALECT}")

message(STATUS "Compiler flags: " ${CMAKE_CXX_FLAGS})

include(AddCatch)
include_directories(${CATCH_INCLUDE_DIR})

# config file
set(CORE8_VERSION_MAJOR 0)
set(CORE8_VERSION_MINOR 1)
set(CORE8_VERSION_PATCH 0)

configure_file(
        "${PROJECT_SOURCE_DIR}/include/core8/Config.hpp.in"
        "${PROJECT_BINARY_DIR}/include/core8/Config.hpp")

include_directories(include)
include_directories(include/core8)

file(GLOB sources src/*.cpp include/*.hpp include/core/*.hpp)

add_library(core8 SHARED ${sources})
set_target_properties(core8 PROPERTIES LINKER_LANGUAGE CXX)

enable_testing(true)
add_subdirectory(test)