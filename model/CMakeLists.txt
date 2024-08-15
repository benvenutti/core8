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

target_link_libraries( ${PROJECT_NAME} PUBLIC Boost::boost )

## tests:

add_executable( model-test-suite
  tests/mock/Helper.hpp
  tests/mock/IoDeviceMock.hpp
  tests/mock/RandomNumberGeneratorMock.hpp
  tests/CPU.assign.test.cpp
  tests/CPU.bcd.test.cpp
  tests/CPU.bitwise.test.cpp
  tests/CPU.conditional.test.cpp
  tests/CPU.constant.test.cpp
  tests/CPU.flow.test.cpp
  tests/CPU.keyboard.test.cpp
  tests/CPU.math.test.cpp
  tests/CPU.memory.test.cpp
  tests/CPU.random.test.cpp
  tests/CPU.timer.test.cpp
  tests/MMU.test.cpp
  tests/OpDecoder.test.cpp
  tests/WordDecoder.test.cpp )

target_link_libraries( model-test-suite PRIVATE ${PROJECT_NAME} Catch2::Catch2WithMain )
add_test( NAME ModelTestSuite COMMAND model-test-suite )
