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

target_compile_features(core8-model PUBLIC cxx_std_20)

set_target_properties(core8-model PROPERTIES COMPILE_WARNING_AS_ERROR ON)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/config/Version.hpp.in
  ${PROJECT_BINARY_DIR}/include/model/Version.hpp
)

target_include_directories(
  core8-model
  PUBLIC
    include
    ${PROJECT_BINARY_DIR}/include
)

# tests:

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()
