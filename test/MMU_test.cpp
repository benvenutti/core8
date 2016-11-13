#include <catch.hpp>

#include <array>
#include <stdexcept>

#include "Chip8.hpp"
#include "MMU.hpp"

namespace {

using namespace Core8;

SCENARIO("MMUs can write bytes to memory", "[write-byte]") {
  GIVEN("An uninitialized memory") {
    std::array<Chip8::BYTE, Chip8::RAM_SIZE> memory{};
    Core8::MMU mmu{memory};

    WHEN("the MMU writes bytes to certain addresses") {
      mmu.writeByte(0x11, 0x0);
      mmu.writeByte(0xAA, 0x500);
      mmu.writeByte(0xFF, 0xFFF);

      THEN("those bytes are copied into memory at the given addresses") {
        REQUIRE(0x11 == memory.at(0x0));
        REQUIRE(0xAA == memory.at(0x500));
        REQUIRE(0xFF == memory.at(0xFFF));
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
    std::array<Chip8::BYTE, Chip8::RAM_SIZE> memory{};
    memory.at(0x80) = 0x11;
    memory.at(0x800) = 0x22;
    memory.at(0xFFF) = 0xFF;
    Core8::MMU mmu{memory};

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
    std::array<Chip8::BYTE, Chip8::RAM_SIZE> memory{};
    memory.at(0x80) = 0x1A;
    memory.at(0x81) = 0xF1;
    memory.at(0xFFE) = 0xCC;
    memory.at(0xFFF) = 0xDD;
    Core8::MMU mmu{memory};

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

SCENARIO("MMUs can clear the memory they handle", "[clear]") {
  GIVEN("A memory with some values") {
    std::array<Core8::Chip8::BYTE, Core8::Chip8::RAM_SIZE> memory{};
    memory.fill(0xFF);
    Core8::MMU mmu{memory};

    WHEN("the MMU clears the memory") {
      mmu.clear();

      THEN("all bytes in memory are set to zero") {
        for (const auto& byte: memory) {
          REQUIRE(byte == 0x0);
        }
      }
    }
  }
}

} // namespace