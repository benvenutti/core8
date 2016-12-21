#include <catch.hpp>

#include <vector>

#include "aux/Aux.hpp"
#include "CPU.hpp"

namespace {

SCENARIO("CPUs can load addresses to the address register I", "[memory]") {
  GIVEN("A CPU") {
    Aux::TestKit testKit;
    Core8::CPU& cpu = testKit.cpu;

    WHEN("the CPU executes a ANNN operation") {
      cpu.setInstruction(0xA123);
      cpu.decode();
      cpu.execute();
      const auto address1 = cpu.getI();

      cpu.setInstruction(0xAFFF);
      cpu.decode();
      cpu.execute();
      const auto address2 = cpu.getI();

      THEN("the address NNN is loaded into the address register I") {
        REQUIRE(0x123 == address1);
        REQUIRE(0xFFF == address2);
      }
    }
  }
}

SCENARIO("CPUs can load the registers into memory", "[memory]") {
  GIVEN("A CPU with initialized V and I registers") {
    const std::vector<Core8::Chip8::BYTE> bytes = {
        0x10, 0x11, 0x12, 0x13, 0x24, 0x25, 0x26, 0x27,
        0x38, 0x39, 0x3A, 0x3B, 0x4C, 0x4D, 0x4E, 0x4F
    };

    Aux::TestKit testKit;
    Core8::CPU& cpu = testKit.cpu;
    cpu.setI(1024);

    for (std::size_t i = 0; i < 16; ++i) {
      cpu.writeRegister(static_cast<Core8::Chip8::REGISTER>(i), bytes[i]);
    }

    WHEN("the CPU executes a FX55 operation") {
      cpu.setInstruction(0xFF55);
      cpu.decode();
      cpu.execute();

      THEN("the registers from V0 to VX are stored in memory starting at address I") {
        const Core8::MMU& mmu = testKit.mmu;
        for (std::size_t i = 0; i < 16; ++i) {
          REQUIRE(mmu.readByte(1024 + i) == bytes[i]);
        }
      }
      AND_THEN("the value of I is incremented by X plus one") {
        REQUIRE(cpu.getI() == 1024 + 0xF + 1);
      }
    }
  }
}

} // unnamed namespace