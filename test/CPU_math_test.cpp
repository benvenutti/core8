#include <catch.hpp>

#include "aux/Aux.hpp"
#include "Chip8.hpp"
#include "CPU.hpp"

namespace {

struct CpuFixture {
  Aux::TestKit testKit;
  Core8::CPU& cpu = testKit.cpu;
};

SCENARIO_METHOD(
    CpuFixture,
    "CPU adds register Y to register X using 8XY4 opcode "
        "without the need for a carry",
    "[math]"
) {
  GIVEN("A CPU with some initialized registers") {
    cpu.writeRegister(Core8::Chip8::Register::V1, 0x11);
    cpu.writeRegister(Core8::Chip8::Register::V4, 0x35);

    WHEN("the CPU executes a 8XY4 opcode") {
      cpu.execute(0x8144);

      THEN("the value of VY is added to VX") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::V1) == 0x46);
      }
      AND_THEN("VF is set to 0 since there is no need for a carry") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::VF) == 0x0);
      }
    }
  }
}

SCENARIO_METHOD(
    CpuFixture,
    "CPU adds register Y to register X using 8XY4 opcode "
        "with the need for a carry",
    "[math]"
) {
  GIVEN("A CPU with some initialized registers") {
    cpu.writeRegister(Core8::Chip8::Register::V1, 0x11);
    cpu.writeRegister(Core8::Chip8::Register::V5, 0xFE);

    WHEN("the CPU executes a 8XY4 opcode") {
      cpu.execute(0x8154);

      THEN("the value of VY is added to VX (with an overflow)") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::V1) == 0xF);
      }
      AND_THEN("VF is set to 1 since there is a carry") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::VF) == 0x1);
      }
    }
  }
}

SCENARIO_METHOD(
    CpuFixture,
    "CPU subtracts register Y from register X using 8XY5 opcode "
        "without the need for a borrow",
    "[math]"
) {
  GIVEN("A CPU with some initialized registers") {
    cpu.writeRegister(Core8::Chip8::Register::VA, 0xA3);
    cpu.writeRegister(Core8::Chip8::Register::VB, 0x15);

    WHEN("the CPU executes a 8XY5 opcode") {
      cpu.execute(0x8AB5);

      THEN("the value of VY is subtracted from VX") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::VA) == 0x8E);
      }
      AND_THEN("VF is set to 1 since there is no borrow") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::VF) == 0x1);
      }
    }
  }
}

SCENARIO_METHOD(
    CpuFixture,
    "CPU subtracts register Y from register X using 8XY5 opcode "
        "with the need for a borrow",
    "[math]"
) {
  GIVEN("A CPU with some initialized registers") {
    cpu.writeRegister(Core8::Chip8::Register::VA, 0xA3);
    cpu.writeRegister(Core8::Chip8::Register::VC, 0xFF);

    WHEN("the CPU executes a 8XY5 opcode") {
      cpu.execute(0x8AC5);

      THEN("the value of VY is subtracted from VX") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::VA) == 0xA4);
      }
      AND_THEN("VF is set to 0 since there is a borrow") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::VF) == 0x0);
      }
    }
  }
}

SCENARIO_METHOD(
    CpuFixture,
    "CPU executes opcode 8XY7 to "
        "subtract register X from register Y (storing the result in VX) "
        "without the need for a borrow",
    "[math]"
) {
  GIVEN("A CPU with some initialized registers") {
    cpu.writeRegister(Core8::Chip8::Register::V3, 0x3F);
    cpu.writeRegister(Core8::Chip8::Register::V4, 0xBB);

    WHEN("the CPU executes a 8XY7 opcode") {
      cpu.execute(0x8347);

      THEN("the the result of VY minus VX is stored in VX") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::V3) == 0x7C);
      }
      AND_THEN("VF is set to 1 since there is no borrow") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::VF) == 0x1);
      }
    }
  }
}

SCENARIO_METHOD(
    CpuFixture,
    "CPU executes opcode 8XY7 to "
        "subtract register X from register Y (storing the result in VX) "
        "with the need for a borrow",
    "[math]"
) {
  GIVEN("A CPU with some initialized registers") {
    cpu.writeRegister(Core8::Chip8::Register::V4, 0xBB);
    cpu.writeRegister(Core8::Chip8::Register::V5, 0xFF);

    WHEN("the CPU executes a 8XY7 opcode") {
      cpu.execute(0x8547);

      THEN("the the result of VY minus VX is stored in VX") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::V5) == 0xBC);
      }
      AND_THEN("VF is set to 1 since there is a borrow") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::VF) == 0x0);
      }
    }
  }
}

} // namespace