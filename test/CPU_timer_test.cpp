#include <catch.hpp>

#include "aux/Aux.hpp"
#include "Chip8.hpp"
#include "CPU.hpp"

namespace {

SCENARIO("CPUs can assign the value of the delay timer to a register", "[timer]") {
  GIVEN("A CPU with an initialized delay timer") {
    Aux::TestKit testKit;
    Core8::CPU& cpu = testKit.cpu;
    const Core8::Chip8::BYTE delay{0x3C};
    cpu.setDelayTimer(delay);

    WHEN("the CPU executes a FX07 operation") {
      cpu.execute(0xF007);
      cpu.execute(0xFE07);

      THEN("the target register holds a copy of the delay timer value") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::V0) == delay);
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::VE) == delay);
      }
    }
  }
}

SCENARIO("CPUs can assign the value of registers to the delay timer", "[timer]") {
  GIVEN("A CPU with initialized registers") {
    Aux::TestKit testKit;
    Core8::CPU& cpu = testKit.cpu;
    cpu.writeRegister(Core8::Chip8::Register::V0, 0x2A);
    cpu.writeRegister(Core8::Chip8::Register::VF, 0xCD);

    WHEN("the CPU executes a FX15 operation") {
      cpu.execute(0xF015);
      const auto delay1 = cpu.getDelayTimer();

      cpu.execute(0xFF15);
      const auto delay2 = cpu.getDelayTimer();

      THEN("the delay timer is updated to the value of the register VX") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::V0) == delay1);
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::VF) == delay2);
      }
    }
  }
}

SCENARIO("CPUs can assign the value of registers to the sound timer", "[timer]") {
  GIVEN("A CPU with initialized registers") {
    Aux::TestKit testKit;
    Core8::CPU& cpu = testKit.cpu;
    cpu.writeRegister(Core8::Chip8::Register::V0, 0xBE);
    cpu.writeRegister(Core8::Chip8::Register::VF, 0xFE);

    WHEN("the CPU executes a FX18 operation") {
      cpu.execute(0xF018);
      const auto sound1 = cpu.getSoundTimer();

      cpu.execute(0xFF18);
      const auto sound2 = cpu.getSoundTimer();

      THEN("the sound timer is updated to the value of the register VX") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::V0) == sound1);
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::VF) == sound2);
      }
    }
  }
}

} // unnamed namespace
