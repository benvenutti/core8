#include <catch.hpp>

#include <stdexcept>

#include "aux/Aux.hpp"
#include "Chip8.hpp"
#include "MMU.hpp"

namespace {

SCENARIO("Creating a MMU", "[mmu]") {
  GIVEN("A null context") {
    WHEN("a MMU object is created") {
      Core8::MMU mmu;

      THEN("its size is equal the Chip-8 ram size") {
        REQUIRE(mmu.getSize() == Core8::Chip8::RAM_SIZE);
      }
    }
  }
}

SCENARIO("MMU writes a byte into a valid address", "[mmu]") {
  GIVEN("A MMU") {
    Core8::MMU mmu;

    WHEN("the MMU writes a byte to a valid address") {
      mmu.writeByte(0x11, 0x0);
      mmu.writeByte(0xFF, 0xFFF);

      THEN("the byte is copied into memory at that address") {
        REQUIRE(0x11 == mmu.readByte(0x0));
        REQUIRE(0xFF == mmu.readByte(0xFFF));
      }
    }
  }
}

SCENARIO("MMU writes a byte into an invalid address", "[mmu]") {
  GIVEN("A MMU") {
    Core8::MMU mmu;

    WHEN("the MMU writes a byte to an invalid address") {
      THEN("the MMU will throw an exception") {
        REQUIRE_THROWS_AS(mmu.writeByte(0xFF, 0x1000), std::out_of_range);
      }
    }
  }
}

SCENARIO("MMU reads a byte from a valid address", "[mmu]") {
  GIVEN("A MMU with initialized values") {
    Core8::MMU mmu;
    mmu.writeByte(0x11, 0x0);
    mmu.writeByte(0xFF, 0xFFF);

    WHEN("the MMU reads a byte from a valid address") {
      const auto byte1 = mmu.readByte(0x0);
      const auto byte2 = mmu.readByte(0xFFF);

      THEN("the MMU will return the byte at that address") {
        REQUIRE(0x11 == byte1);
        REQUIRE(0xFF == byte2);
      }
    }
  }
}

SCENARIO("MMU reads a byte from an invalid address", "[mmu]") {
  GIVEN("A MMU") {
    Core8::MMU mmu;

    WHEN("the MMU reads a byte from an invalid address") {
      THEN("the MMU will throw an exception") {
        REQUIRE_THROWS_AS(mmu.readByte(0x1000), std::out_of_range);
      }
    }
  }
}

SCENARIO("MMU reads a word from a valid address", "[mmu]") {
  GIVEN("A MMU with initialized values") {
    Core8::MMU mmu;
    mmu.writeByte(0x1A, 0x80);
    mmu.writeByte(0xF1, 0x81);
    mmu.writeByte(0xCC, 0xFFE);
    mmu.writeByte(0xDD, 0xFFF);

    WHEN("the MMU reads a word from a valid address") {
      const auto word1 = mmu.readWord(0x80);
      const auto word2 = mmu.readWord(0xFFE);

      THEN("the MMU will return the big-endian word starting at that address") {
        REQUIRE(0x1AF1 == word1);
        REQUIRE(0xCCDD == word2);
      }
    }
  }
}

SCENARIO("MMU reads a word from an invalid address", "[mmu]") {
  GIVEN("A MMU") {
    Core8::MMU mmu;

    WHEN("the MMU reads a word from an invalid address") {
      THEN("the MMU will throw an exception") {
        REQUIRE_THROWS_AS(mmu.readWord(0xFFF), std::out_of_range);
      }
    }
  }
}

SCENARIO("MMU loads a rom into memory", "[mmu]") {
  GIVEN("A rom and a cleared MMU") {
    std::vector<std::uint8_t> data{0xFF, 0x11, 0xCC, 0x33};
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
        for (auto address = 0x0u; address < 0x100u; ++address) {
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

SCENARIO("MMU clears its memory", "[mmu]") {
  GIVEN("A MMU with initialized values") {
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