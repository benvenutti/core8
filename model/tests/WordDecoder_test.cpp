#include <catch.hpp>

#include "WordDecoder.hpp"

namespace {

TEST_CASE("Decode X from pattern vXvv", "[decoder]") {
  REQUIRE(Core8::WordDecoder::readX(0x0F00) == 0XF);
  REQUIRE(Core8::WordDecoder::readX(0xF0FF) == 0X0);
}

TEST_CASE("Decode Y from pattern vvYv", "[decoder]") {
  REQUIRE(Core8::WordDecoder::readY(0x00F0) == 0XF);
  REQUIRE(Core8::WordDecoder::readY(0xFF0F) == 0X0);
}

TEST_CASE("Decode N from pattern vvvN", "[decoder]") {
  REQUIRE(Core8::WordDecoder::readN(0x000F) == 0XF);
  REQUIRE(Core8::WordDecoder::readN(0xFFF0) == 0X0);
}

TEST_CASE("Decode NN from pattern vvNN", "[decoder]") {
  REQUIRE(Core8::WordDecoder::readNN(0x00FF) == 0XFF);
  REQUIRE(Core8::WordDecoder::readNN(0xFF11) == 0X11);
}

TEST_CASE("Decode NNN from pattern vNNN", "[decoder]") {
  REQUIRE(Core8::WordDecoder::readNNN(0x0FFF) == 0XFFF);
  REQUIRE(Core8::WordDecoder::readNNN(0xF111) == 0X111);
}

} // namespace