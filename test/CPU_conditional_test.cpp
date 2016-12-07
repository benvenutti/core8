#include <catch.hpp>

#include "Chip8.hpp"
#include "CPU.hpp"

namespace {

using namespace Core8;

SCENARIO("CPUs can skip instructions if a register equals a constant value", "[conditional]") {
  GIVEN("A CPU with some initialized registers") {
    CPU cpu{};
    cpu.writeRegister(Chip8::REGISTER::V1, 0x11);
    cpu.writeRegister(Chip8::REGISTER::V4, 0x35);
    const auto pc0 = cpu.getPc();

    WHEN("the CPU executes a 3XNN opcode on matching register x constant") {
      cpu.setInstruction(0x3111);
      cpu.decode();
      cpu.execute();
      const auto pc1 = cpu.getPc();

      cpu.setInstruction(0x3435);
      cpu.decode();
      cpu.execute();
      const auto pc2 = cpu.getPc();

      THEN("the CPUs program counter is updated") {
        REQUIRE(pc1 == pc0 + Chip8::INSTRUCTION_BYTE_SIZE);
        REQUIRE(pc2 == pc0 + 2 * Chip8::INSTRUCTION_BYTE_SIZE);
      }
    }
    AND_WHEN("the CPU executes a 3XNN opcode on non-matching register x constant") {
      cpu.setInstruction(0x31FF);
      cpu.decode();
      cpu.execute();
      const auto pc1 = cpu.getPc();

      cpu.setInstruction(0x34EE);
      cpu.decode();
      cpu.execute();
      const auto pc2 = cpu.getPc();

      THEN("the CPUs program counter is remains unchanged") {
        REQUIRE(pc1 == pc0);
        REQUIRE(pc2 == pc0);
      }
    }
  }
}

SCENARIO("CPUs can skip instructions if a register differs from a constant", "[conditional]") {
  GIVEN("A CPU with some initialized registers") {
    CPU cpu{};
    cpu.writeRegister(Chip8::REGISTER::VA, 0x1A);
    cpu.writeRegister(Chip8::REGISTER::VB, 0x2B);
    const auto pc0 = cpu.getPc();

    WHEN("the CPU executes a 4XNN opcode on non-matching register x constant") {
      cpu.setInstruction(0x4AA1);
      cpu.decode();
      cpu.execute();
      const auto pc1 = cpu.getPc();

      cpu.setInstruction(0x4BB2);
      cpu.decode();
      cpu.execute();
      const auto pc2 = cpu.getPc();

      THEN("the CPUs program counter is updated") {
        REQUIRE(pc1 == pc0 + Chip8::INSTRUCTION_BYTE_SIZE);
        REQUIRE(pc2 == pc0 + 2 * Chip8::INSTRUCTION_BYTE_SIZE);
      }
    }
    WHEN("the CPU executes a 4XNN opcode on matching register x constant") {
      cpu.setInstruction(0x4A1A);
      cpu.decode();
      cpu.execute();
      const auto pc1 = cpu.getPc();

      cpu.setInstruction(0x4B2B);
      cpu.decode();
      cpu.execute();
      const auto pc2 = cpu.getPc();

      THEN("the CPUs program counter is remains unchanged") {
        REQUIRE(pc1 == pc0);
        REQUIRE(pc2 == pc0);
      }
    }
  }
}

} // unnamed namespace