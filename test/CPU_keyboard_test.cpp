#include <catch.hpp>

#include "aux/Aux.hpp"
#include "CPU.hpp"

namespace {

struct CpuFixture {
  Aux::TestKit testKit;
  Core8::CPU& cpu = testKit.cpu;
  Aux::IoConnectorMock& ioConnector = testKit.ioConnector;
};

SCENARIO_METHOD(
    CpuFixture,
    "Operation EX9E skips next instruction when VX is pressed", "[keyboard]"
) {
  GIVEN("A CPU with V0 set to 0 and an i/o connector with the key 0 pressed") {
    cpu.writeRegister(Core8::Chip8::REGISTER::V0, 0u);
    ioConnector.setPressedKey(Core8::Chip8::KEY::K0);
    const auto originalPc = cpu.getPc();

    WHEN("the CPU executes an EX9E operation with X equal to 0") {
      cpu.setInstruction(0xE09E);
      cpu.decode();
      cpu.execute();

      THEN("the program counter is updated to skip the next instruction") {
        REQUIRE(cpu.getPc() == (originalPc + Core8::Chip8::INSTRUCTION_BYTE_SIZE));
      }
    }
  }
}

SCENARIO_METHOD(
    CpuFixture,
    "Operation EX9E does not skip instruction when VX is not pressed", "[keyboard]"
) {
  GIVEN("A CPU with V0 set to 0 and an i/o connector with the key 1 pressed") {
    cpu.writeRegister(Core8::Chip8::REGISTER::V0, 0u);
    ioConnector.setPressedKey(Core8::Chip8::KEY::K1);
    const auto originalPc = cpu.getPc();

    WHEN("the CPU executes an EX9E operation with X equal to 0") {
      cpu.setInstruction(0xE09E);
      cpu.decode();
      cpu.execute();

      THEN("the program counter remains unchanged") {
        REQUIRE(cpu.getPc() == originalPc);
      }
    }
  }
}

SCENARIO_METHOD(
    CpuFixture,
    "Operation EXA1 skips next instruction when VX is not pressed", "[keyboard]"
) {
  GIVEN("A CPU with V0 set to 1 and an i/o connector with the key 0 pressed") {
    cpu.writeRegister(Core8::Chip8::REGISTER::V0, 1u);
    ioConnector.setPressedKey(Core8::Chip8::KEY::K0);
    const auto originalPc = cpu.getPc();

    WHEN("the CPU executes an EXA1 operation with X equal to 0") {
      cpu.setInstruction(0xE0A1);
      cpu.decode();
      cpu.execute();

      THEN("the program counter is updated to skip the next instruction") {
        REQUIRE(cpu.getPc() == (originalPc + Core8::Chip8::INSTRUCTION_BYTE_SIZE));
      }
    }
  }
}

SCENARIO_METHOD(
    CpuFixture,
    "Operation EXA1 does not skip instruction when VX is pressed", "[keyboard]"
) {
  GIVEN("A CPU with V0 set to 0 and an i/o connector with the key 0 pressed") {
    cpu.writeRegister(Core8::Chip8::REGISTER::V0, 0u);
    ioConnector.setPressedKey(Core8::Chip8::KEY::K0);
    const auto originalPc = cpu.getPc();

    WHEN("the CPU executes an EXA1 operation with X equal to 0") {
      cpu.setInstruction(0xE0A1);
      cpu.decode();
      cpu.execute();

      THEN("the program counter is updated to skip the next instruction") {
        REQUIRE(cpu.getPc() == originalPc);
      }
    }
  }
}

} // unnamed namespace