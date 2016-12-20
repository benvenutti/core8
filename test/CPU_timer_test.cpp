#include <catch.hpp>

#include "aux/Aux.hpp"
#include "Chip8.hpp"
#include "CPU.hpp"

namespace {

SCENARIO("CPUs can assign the value of the delay timer to a register", "[timer]") {
  GIVEN("A CPU with an initialized delay timer") {
    Aux::TestKit testKit;
    Core8::CPU& cpu = testKit.cpu;
    cpu.setDelayTimer(0x3C);

    WHEN("the CPU executes a FX07 operation") {
      cpu.setInstruction(0xF007);
      cpu.decode();
      cpu.execute();
      cpu.setInstruction(0xFE07);
      cpu.decode();
      cpu.execute();

      THEN("the target register holds a copy of the delay timer value") {
        const auto delay = cpu.getDelayTimer();
        REQUIRE(cpu.readRegister(Core8::Chip8::REGISTER::V0) == delay);
        REQUIRE(cpu.readRegister(Core8::Chip8::REGISTER::VE) == delay);
      }
    }
  }
}

SCENARIO("CPUs can assign the value of registers to the delay timer", "[timer]") {
  GIVEN("A CPU with initialized registers") {
    Aux::TestKit testKit;
    Core8::CPU& cpu = testKit.cpu;
    cpu.writeRegister(Core8::Chip8::REGISTER::V0, 0x2A);
    cpu.writeRegister(Core8::Chip8::REGISTER::VF, 0xCD);

    WHEN("the CPU executes a FX15 operation") {
      cpu.setInstruction(0xF015);
      cpu.decode();
      cpu.execute();
      const auto delay1 = cpu.getDelayTimer();
      cpu.setInstruction(0xFF15);
      cpu.decode();
      cpu.execute();
      const auto delay2 = cpu.getDelayTimer();

      THEN("the delay timer is updated to the value of the register VX") {
        REQUIRE(cpu.readRegister(Core8::Chip8::REGISTER::V0) == delay1);
        REQUIRE(cpu.readRegister(Core8::Chip8::REGISTER::VF) == delay2);
      }
    }
  }
}

SCENARIO("CPUs can assign the value of registers to the sound timer", "[timer]") {
  GIVEN("A CPU with initialized registers") {
    Aux::TestKit testKit;
    Core8::CPU& cpu = testKit.cpu;
    cpu.writeRegister(Core8::Chip8::REGISTER::V0, 0xBE);
    cpu.writeRegister(Core8::Chip8::REGISTER::VF, 0xFE);

    WHEN("the CPU executes a FX18 operation") {
      cpu.setInstruction(0xF018);
      cpu.decode();
      cpu.execute();
      const auto sound1 = cpu.getSoundTimer();
      cpu.setInstruction(0xFF18);
      cpu.decode();
      cpu.execute();
      const auto sound2 = cpu.getSoundTimer();

      THEN("the sound timer is updated to the value of the register VX") {
        REQUIRE(cpu.readRegister(Core8::Chip8::REGISTER::V0) == sound1);
        REQUIRE(cpu.readRegister(Core8::Chip8::REGISTER::VF) == sound2);
      }
    }
  }
}

} // unnamed namespace
