project( core8-model VERSION 0.1.0 LANGUAGES CXX )

## files:

set( headers
  include/model/Chip8.hpp
  include/model/CPU.hpp
  include/model/IoDevice.hpp
  include/model/MersenneByteTwister.hpp
  include/model/MMU.hpp
  include/model/OpDecoder.hpp
  include/model/RandomNumberGenerator.hpp
  include/model/VM.hpp
  include/model/WordDecoder.hpp )

set( sources
  src/CPU.cpp
  src/VM.cpp )

configure_file(
  ${PROJECT_SOURCE_DIR}/config/Version.hpp.in
  ${PROJECT_BINARY_DIR}/include/model/Version.hpp )

## library:

add_library( ${PROJECT_NAME} ${headers} ${sources} )
set_target_properties( ${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX CXX_STANDARD 14 )

target_include_directories( ${PROJECT_NAME}
  PUBLIC
    include
    ${PROJECT_BINARY_DIR}/include
  PRIVATE
    include/model )

## tests:

add_executable( model-test-suite
  tests/aux/Aux.hpp
  tests/aux/IoDeviceMock.hpp
  tests/aux/RandomNumberGeneratorMock.hpp
  tests/CPU_assign_test.cpp
  tests/CPU_bcd_test.cpp
  tests/CPU_bitwise_test.cpp
  tests/CPU_conditional_test.cpp
  tests/CPU_constant_test.cpp
  tests/CPU_flow_test.cpp
  tests/CPU_keyboard_test.cpp
  tests/CPU_math_test.cpp
  tests/CPU_memory_test.cpp
  tests/CPU_random_test.cpp
  tests/CPU_timer_test.cpp
  tests/MMU_test.cpp
  tests/OpDecoder_test.cpp
  tests/WordDecoder_test.cpp
  tests/catch_setup.cpp )

target_link_libraries( model-test-suite PRIVATE ${PROJECT_NAME} catch2 )
add_test( NAME ModelTestSuite COMMAND model-test-suite )
