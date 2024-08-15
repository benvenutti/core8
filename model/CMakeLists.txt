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

add_subdirectory(tests)
