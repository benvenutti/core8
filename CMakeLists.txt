cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(core8 VERSION 0.1.0 LANGUAGES CXX)

## build settings:

set(CMAKE_CXX_STANDARD 14)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG -g)
set(CMAKE_CXX_FLAGS_RELEASE -O3)

## 3rd party dependencies:

add_library(catch INTERFACE)
target_include_directories(catch INTERFACE libs/Catch2/single_include)

find_package(Qt5Widgets REQUIRED)

## compiler definitions:

add_definitions(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast
  -Wcast-align -Wcast-qual -Wunused -Woverloaded-virtual -pedantic)

## folders:

enable_testing(true)
add_subdirectory(model)
add_subdirectory(app)
