cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

# project:

project(
  core8
  VERSION      0.1.0
  DESCRIPTION  "core8 is a CHIP8 emulator that offers a Qt GUI to run CHIP8 binaries"
  HOMEPAGE_URL https://github.com/benvenutti/core8
  LANGUAGES    CXX
)

option(BUILD_TESTS "Build tests" ON)

# 3rd party dependencies:

find_package(Qt6 6.5 COMPONENTS Widgets REQUIRED)

if(BUILD_TESTS)
  include(FetchContent)

  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.0.1
  )

  FetchContent_MakeAvailable(Catch2)
endif()

# build settings:

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release FORCE)
endif()

set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

# testing:

if(BUILD_TESTS)
  enable_testing()
endif()

# compiler's warning messages:

if(MSVC)
  add_compile_options(
    # warnings:
    /W4 /w14545 /w34242 /w34254 /w34287 /w44263 /w44265 /w44296 /w44311 /w44826
    /we4289 /w14546 /w14547 /w14549 /w14555 /w14619 /w14905 /w14906 /w14928

    # optimization levels:
    $<$<CONFIG:RELEASE>:/O2>
    $<$<CONFIG:DEBUG>:/Od>
  )
else()
  add_compile_options(
    # warnings:
    -Wall -Wconversion -Wsign-conversion -Wshadow -Wnon-virtual-dtor -Wcast-qual
    -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -pedantic -Wextra

    # optimization levels:
    $<$<CONFIG:RELEASE>:-O3>
    $<$<CONFIG:DEBUG>:-O0>
  )
endif()

# subdirectories:

add_subdirectory(model)
add_subdirectory(app-qtwidget)
