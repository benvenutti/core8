cmake_minimum_required( VERSION 3.8 FATAL_ERROR )
project( core8-emulator VERSION 0.1.0 LANGUAGES CXX )

## cmake policies:

if ( POLICY CMP0074 )
  cmake_policy( SET CMP0074 NEW )
endif()

## build settings:

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release FORCE )
endif()

if( CMAKE_BUILD_TYPE MATCHES Coverage )
  add_compile_options( -g -O0 --coverage )
  set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov --coverage" )
  set( CMAKE_BUILD_TYPE Debug FORCE )
endif()

set( CMAKE_CXX_STANDARD 14 )
set( CXX_STANDARD_REQUIRED ON )
set( CXX_EXTENSIONS OFF )
set( CMAKE_CXX_FLAGS_RELEASE -O3 )

## 3rd party dependencies:

add_library( catch2 INTERFACE )
target_include_directories( catch2 INTERFACE libs/Catch2/single_include )

find_package( Qt5Widgets REQUIRED )
find_package( Boost 1.54 REQUIRED )

## compiler definitions:

if( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
  add_compile_options( /W4 /w14545 /w34242 /w34254 /w34287 /w44263 /w44265 
    /w44296 /w44311 /w44826 /we4289 /w14546 /w14547 /w14549 /w14555 /w14619 
    /w14905 /w14906 /w14928 )
elseif( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
  add_compile_options( -Wall -Wextra -Wconversion -Wsign-conversion -Wshadow
    -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wcast-qual -Wunused
    -Woverloaded-virtual -pedantic )
endif()

## folders:

enable_testing( true )
add_subdirectory( model )
add_subdirectory( app )
