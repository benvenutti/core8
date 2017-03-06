#include <catch.hpp>

#include "aux/Aux.hpp"
#include "CPU.hpp"

namespace {

struct CpuFixture {
  Aux::TestKit testKit;
  Core8::CPU& cpu = testKit.cpu;
  Aux::IoDeviceMock& ioDevice = testKit.ioDevice;
};

SCENARIO_METHOD(
    CpuFixture,
    "Operation EX9E skips next instruction when VX is pressed", "[keyboard]"
) {
  GIVEN("A CPU with V0 set to 0 and an i/o connector with the key 0 pressed") {
    cpu.writeRegister(Core8::Chip8::Register::V0, 0u);
    ioDevice.setPressedKey(Core8::Chip8::Key::K0);
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
    cpu.writeRegister(Core8::Chip8::Register::V0, 0u);
    ioDevice.setPressedKey(Core8::Chip8::Key::K1);
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
    cpu.writeRegister(Core8::Chip8::Register::V0, 1u);
    ioDevice.setPressedKey(Core8::Chip8::Key::K0);
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
    cpu.writeRegister(Core8::Chip8::Register::V0, 0u);
    ioDevice.setPressedKey(Core8::Chip8::Key::K0);
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

SCENARIO_METHOD(
    CpuFixture,
    "Operation FX0A halts the CPU when no key is pressed", "[keyboard]"
) {
  GIVEN("A CPU and an i/o connector with no key pressed") {
    ioDevice.setPressedKey(Core8::Chip8::Key::NONE);
    const auto originalV0 = cpu.readRegister(Core8::Chip8::Register::V0);
    const auto originalPc = cpu.getPc();

    WHEN("the CPU executes an FX0A operation with X equal to 0") {
      cpu.setInstruction(0xF00A);
      cpu.decode();
      cpu.execute();

      THEN("the program counter remains unchanged (the CPU is halted)") {
        REQUIRE(cpu.getPc() == originalPc);
      }
      AND_THEN("register V0 remains unchanged") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::V0) == originalV0);
      }
    }
  }
}

SCENARIO_METHOD(
    CpuFixture,
    "Operation FX0A sets register to the value of the pressed key", "[keyboard]"
) {
  GIVEN("a CPU and an i/o connector with the key F pressed") {
    ioDevice.setPressedKey(Core8::Chip8::Key::KF);
    const auto originalPc = cpu.getPc();

    WHEN("the CPU executes an FX0A operation with X equal to 0") {
      cpu.setInstruction(0xF00A);
      cpu.decode();
      cpu.execute();

      THEN("the program counter remains unchanged (the CPU is halted)") {
        REQUIRE(cpu.getPc() == (originalPc + Core8::Chip8::INSTRUCTION_BYTE_SIZE));
      }
      AND_THEN("the pressed key value F is stored in V0") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::V0) == 0xF);
      }
    }
  }
}

} // unnamed namespace