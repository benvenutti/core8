add_library(
  core8-model
  STATIC
  include/model/Chip8.hpp
  include/model/CPU.hpp
  include/model/IoDevice.hpp
  include/model/MersenneByteTwister.hpp
  include/model/MMU.hpp
  include/model/OpDecoder.hpp
  include/model/RandomNumberGenerator.hpp
  include/model/VM.hpp
  include/model/WordDecoder.hpp
  src/CPU.cpp
  src/VM.cpp
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/config/Version.hpp.in
  ${PROJECT_BINARY_DIR}/include/model/Version.hpp
)

target_link_libraries(core8-model PUBLIC Boost::boost)

target_include_directories(
  core8-model
  PUBLIC
    include
    ${PROJECT_BINARY_DIR}/include
)

target_compile_features(core8-model PUBLIC cxx_std_14)

# tests:

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

target_link_libraries( model-test-suite PRIVATE core8-model Catch2::Catch2WithMain )
add_test( NAME ModelTestSuite COMMAND model-test-suite )
