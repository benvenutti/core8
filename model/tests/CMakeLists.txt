add_executable(
  model_tests
  mock/Helper.hpp
  mock/IoDeviceMock.hpp
  mock/RandomNumberGeneratorMock.hpp
  CPU.assign.test.cpp
  CPU.bcd.test.cpp
  CPU.bitwise.test.cpp
  CPU.conditional.test.cpp
  CPU.constant.test.cpp
  CPU.flow.test.cpp
  CPU.keyboard.test.cpp
  CPU.math.test.cpp
  CPU.memory.test.cpp
  CPU.random.test.cpp
  CPU.timer.test.cpp
  MMU.test.cpp
  OpDecoder.test.cpp
  Version.test.cpp
  WordDecoder.test.cpp
)

target_compile_features(model_tests PUBLIC cxx_std_20)

set_target_properties(model_tests PROPERTIES COMPILE_WARNING_AS_ERROR ON)

target_link_libraries(model_tests PRIVATE core8-model Catch2::Catch2WithMain)

target_include_directories(model_tests PUBLIC .)

add_test(NAME ModelTestSuite COMMAND model_tests)
