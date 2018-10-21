cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(core8 VERSION 0.1.0 LANGUAGES CXX)

## build settings:

set(CMAKE_CXX_STANDARD 14)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE MATCHES Coverage)
  add_compile_options( -g -O0 --coverage)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov --coverage")
  set(CMAKE_BUILD_TYPE Debug FORCE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

## 3rd party dependencies:

add_library(catch INTERFACE)
target_include_directories(catch INTERFACE libs/Catch2/single_include)

find_package(Qt5Widgets REQUIRED)
find_package(Boost REQUIRED)

## compiler definitions:

add_definitions(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast
  -Wcast-align -Wcast-qual -Wunused -Woverloaded-virtual -pedantic)

## folders:

enable_testing(true)
add_subdirectory(model)
add_subdirectory(app)
