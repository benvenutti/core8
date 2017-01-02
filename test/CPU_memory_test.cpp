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
    const std::vector<Core8::Chip8::BYTE> bytes{
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
        for (std::size_t i = 0; i < 0xF; ++i) {
          REQUIRE(mmu.readByte(1024 + i) == bytes[i]);
        }
      }
      AND_THEN("the value of I is incremented by X plus one") {
        REQUIRE(cpu.getI() == 1024 + 0xF + 1);
      }
    }
  }
}

SCENARIO("CPUs can load values from memory into registers", "[memory]") {
  GIVEN("A CPU with initialized memory and register I") {
    Aux::TestKit testKit;
    Core8::CPU& cpu = testKit.cpu;
    Core8::MMU& mmu = testKit.mmu;

    cpu.setI(1024);

    std::vector<Core8::Chip8::BYTE> bytes = { 0x10, 0x11, 0x12, 0x13, 0x24, 0x25 };
    Aux::ByteStream rom{bytes};
    mmu.load(rom, 1024);

    WHEN("the CPU executes a FX65 operation") {
      cpu.setInstruction(0xF565);
      cpu.decode();
      cpu.execute();

      THEN("registers V0 to VX are filled with values from memory starting at address I") {
        for (std::size_t i = 0; i < 0x5; ++i) {
          REQUIRE(cpu.readRegister(static_cast<Core8::Chip8::REGISTER>(i)) == bytes[i]);
        }
      }
      AND_THEN("the value of I is incremented by X plus one") {
        REQUIRE(cpu.getI() == 1024 + 0x5 + 1);
      }
    }
  }
}

SCENARIO("CPUs can add registers to the address register I", "[memory]") {
  GIVEN("A CPU with registers V and I initialized") {
    Aux::TestKit testKit;
    Core8::CPU& cpu = testKit.cpu;
    cpu.writeRegister(Core8::Chip8::REGISTER::V0, 10);
    cpu.writeRegister(Core8::Chip8::REGISTER::VE, 66);
    cpu.setI(512);

    WHEN("the CPU executes a FX1E operation") {
      cpu.setInstruction(0xF01E);
      cpu.decode();
      cpu.execute();
      const auto address1 = cpu.getI();

      cpu.setInstruction(0xFE1E);
      cpu.decode();
      cpu.execute();
      const auto address2 = cpu.getI();

      THEN("the value of register Vx is added to the address register I") {
        REQUIRE(522 == address1);
        REQUIRE(588 == address2);
      }
    }
  }
}

SCENARIO("CPUs can load to I the address of the sprite for the character in Vx", "[memory]") {
  GIVEN("A CPU with registers Vx initialized") {
    Aux::TestKit testKit;
    Core8::CPU& cpu = testKit.cpu;
    cpu.writeRegister(Core8::Chip8::REGISTER::V0, 0x0);
    cpu.writeRegister(Core8::Chip8::REGISTER::VE, 0xF);

    WHEN("the CPU executes a FX29 operation") {
      cpu.setInstruction(0xF029);
      cpu.decode();
      cpu.execute();
      const auto address1 = cpu.getI();

      cpu.setInstruction(0xFE29);
      cpu.decode();
      cpu.execute();
      const auto address2 = cpu.getI();

      THEN("register I is updated with the address of the character sprite of Vx value") {
        REQUIRE(address1 == 0);
        REQUIRE(address2 == 75);
      }
    }
  }
}

} // unnamed namespace