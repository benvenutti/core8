#include <catch.hpp>

#include <array>
#include <stdexcept>

#include "aux/Aux.hpp"
#include "Chip8.hpp"
#include "MMU.hpp"

namespace {

using namespace Core8;

SCENARIO("MMUs can write bytes to memory", "[write-byte]") {
  GIVEN("An uninitialized memory") {
    Core8::MMU mmu;

    WHEN("the MMU writes bytes to certain addresses") {
      mmu.writeByte(0x11, 0x0);
      mmu.writeByte(0xAA, 0x500);
      mmu.writeByte(0xFF, 0xFFF);

      THEN("those bytes are copied into memory at the given addresses") {
        REQUIRE(0x11 == mmu.readByte(0x0));
        REQUIRE(0xAA == mmu.readByte(0x500));
        REQUIRE(0xFF == mmu.readByte(0xFFF));
      }
    }
    WHEN("the MMU writes bytes at invalid addresses") {
      THEN("the MMU will throw an exception") {
        REQUIRE_THROWS_AS(mmu.writeByte(0xFF, 0x1000), std::out_of_range);
      }
    }
  }
}

SCENARIO("MMUs can read bytes from memory", "[read-byte]") {
  GIVEN("A memory with some values") {
    Core8::MMU mmu;
    mmu.writeByte(0x11, 0x80);
    mmu.writeByte(0x22, 0x800);
    mmu.writeByte(0xFF, 0xFFF);

    WHEN("the MMU reads bytes from certain addresses") {
      const auto byte1 = mmu.readByte(0x80);
      const auto byte2 = mmu.readByte(0x800);
      const auto byte3 = mmu.readByte(0xFFF);

      THEN("the MMU will return the bytes at those addresses") {
        REQUIRE(0x11 == byte1);
        REQUIRE(0x22 == byte2);
        REQUIRE(0xFF == byte3);
      }
    }
    WHEN("the MMU reads bytes from invalid addresses") {
      THEN("the MMU will throw an exception") {
        REQUIRE_THROWS_AS(mmu.readByte(0x1000), std::out_of_range);
      }
    }
  }
}

SCENARIO("MMUs can read words from memory", "[read-word]") {
  GIVEN("A memory with some values") {
    Core8::MMU mmu;
    mmu.writeByte(0x1A, 0x80);
    mmu.writeByte(0xF1, 0x81);
    mmu.writeByte(0xCC, 0xFFE);
    mmu.writeByte(0xDD, 0xFFF);

    WHEN("the MMU reads words from certain addresses") {
      const auto word1 = mmu.readWord(0x80);
      const auto word2 = mmu.readWord(0xFFE);

      THEN("the MMU will return the big-endian words starting at those addresses") {
        REQUIRE(0x1AF1 == word1);
        REQUIRE(0xCCDD == word2);
      }
    }
    WHEN("the MMU reads words from invalid addresses") {
      THEN("the MMU will throw an exception") {
        REQUIRE_THROWS_AS(mmu.readWord(0xFFF), std::out_of_range);
      }
    }
  }
}

SCENARIO("MMUs can load roms into memory", "[load]") {
  GIVEN("A rom") {
    std::vector<std::uint8_t> data{{ 0xFF, 0x11, 0xCC, 0x33 }};
    Aux::ByteStream rom{data};

    Core8::MMU mmu;
    mmu.clear();

    WHEN("the MMU loads the rom at a certain address") {
      mmu.load(rom, 0x100);

      THEN("the whole rom is copied into memory starting at the given address") {
        REQUIRE(0xFF == mmu.readByte(0x100));
        REQUIRE(0x11 == mmu.readByte(0x101));
        REQUIRE(0xCC == mmu.readByte(0x102));
        REQUIRE(0x33 == mmu.readByte(0x103));
      }
      AND_THEN("the rest of memory remains unchanged") {
        for (auto address = 0x0; address < 0x100; ++address) {
          REQUIRE(0x0 == mmu.readByte(address));
        }

        const auto memorySize = mmu.getSize();
        for (auto address = 0x104u; address < memorySize; ++address) {
          REQUIRE(0x0 == mmu.readByte(address));
        }
      }
    }
  }
}

SCENARIO("MMUs can clear the memory they handle", "[clear]") {
  GIVEN("A memory with some values") {
    Core8::MMU mmu;
    mmu.writeByte(0x1A, 0x80);

    WHEN("the MMU clears the memory") {
      mmu.clear();

      THEN("all bytes in memory are set to zero") {
        const auto memorySize = mmu.getSize();
        for (auto i = 0u; i < memorySize; ++i) {
          REQUIRE(mmu.readByte(i) == 0x0);
        }
      }
    }
  }
}

} // namespace