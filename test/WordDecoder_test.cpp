#include <catch.hpp>

#include "WordDecoder.hpp"

namespace {

using namespace Core8;

TEST_CASE("Decode X from pattern vXvv", "[decoder]") {
  REQUIRE(WordDecoder::readX(0x0F00) == 0XF);
  REQUIRE(WordDecoder::readX(0xF0FF) == 0X0);
}

} // unnamed namespace