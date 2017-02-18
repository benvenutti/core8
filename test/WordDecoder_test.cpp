#include <catch.hpp>

#include "WordDecoder.hpp"

namespace {

using namespace Core8;

TEST_CASE("Decode X from pattern vXvv", "[decoder]") {
  REQUIRE(WordDecoder::readX(0x0F00) == 0XF);
  REQUIRE(WordDecoder::readX(0xF0FF) == 0X0);
}

TEST_CASE("Decode Y from pattern vvYv", "[decoder]") {
  REQUIRE(WordDecoder::readY(0x00F0) == 0XF);
  REQUIRE(WordDecoder::readY(0xFF0F) == 0X0);
}

TEST_CASE("Decode N from pattern vvvN", "[decoder]") {
  REQUIRE(WordDecoder::readN(0x000F) == 0XF);
  REQUIRE(WordDecoder::readN(0xFFF0) == 0X0);
}

TEST_CASE("Decode NN from pattern vvNN", "[decoder]") {
  REQUIRE(WordDecoder::readNN(0x00FF) == 0XFF);
  REQUIRE(WordDecoder::readNN(0xFF11) == 0X11);
}

} // unnamed namespace