#include <catch.hpp>

#include "aux/Aux.hpp"
#include "Chip8.hpp"
#include "CPU.hpp"

namespace {

using namespace Core8;

SCENARIO("CPUs can skip instructions if a register equals a constant value", "[conditional]") {
  GIVEN("A CPU with some initialized registers") {
    Aux::TestKit testKit;
    CPU& cpu = testKit.cpu;
    cpu.writeRegister(Chip8::Register::V1, 0x11);
    cpu.writeRegister(Chip8::Register::V4, 0x35);
    const auto pc0 = cpu.getPc();

    WHEN("the CPU executes a 3XNN opcode on matching register x constant") {
      cpu.execute(0x3111);
      const auto pc1 = cpu.getPc();

      cpu.execute(0x3435);
      const auto pc2 = cpu.getPc();

      THEN("the CPUs program counter is updated") {
        REQUIRE(pc1 == pc0 + Chip8::INSTRUCTION_BYTE_SIZE);
        REQUIRE(pc2 == pc0 + 2 * Chip8::INSTRUCTION_BYTE_SIZE);
      }
    }
    AND_WHEN("the CPU executes a 3XNN opcode on non-matching register x constant") {
      cpu.execute(0x31FF);
      const auto pc1 = cpu.getPc();

      cpu.execute(0x34EE);
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
    Aux::TestKit testKit;
    CPU& cpu = testKit.cpu;
    cpu.writeRegister(Chip8::Register::VA, 0x1A);
    cpu.writeRegister(Chip8::Register::VB, 0x2B);
    const auto pc0 = cpu.getPc();

    WHEN("the CPU executes a 4XNN opcode on non-matching register x constant") {
      cpu.execute(0x4AA1);
      const auto pc1 = cpu.getPc();

      cpu.execute(0x4BB2);
      const auto pc2 = cpu.getPc();

      THEN("the CPUs program counter is updated") {
        REQUIRE(pc1 == pc0 + Chip8::INSTRUCTION_BYTE_SIZE);
        REQUIRE(pc2 == pc0 + 2 * Chip8::INSTRUCTION_BYTE_SIZE);
      }
    }
    AND_WHEN("the CPU executes a 4XNN opcode on matching register x constant") {
      cpu.execute(0x4A1A);
      const auto pc1 = cpu.getPc();

      cpu.execute(0x4B2B);
      const auto pc2 = cpu.getPc();

      THEN("the CPUs program counter is remains unchanged") {
        REQUIRE(pc1 == pc0);
        REQUIRE(pc2 == pc0);
      }
    }
  }
}

SCENARIO("CPUs can skip instructions if a register equals another", "[conditional]") {
  GIVEN("A CPU with some initialized registers") {
    Aux::TestKit testKit;
    CPU& cpu = testKit.cpu;
    cpu.writeRegister(Chip8::Register::V0, 0x47);
    cpu.writeRegister(Chip8::Register::VF, 0xE3);
    cpu.writeRegister(Chip8::Register::V2, 0x47);
    cpu.writeRegister(Chip8::Register::V3, 0xE3);
    cpu.writeRegister(Chip8::Register::V8, 0xE1);
    cpu.writeRegister(Chip8::Register::V9, 0xE0);
    const auto pc0 = cpu.getPc();

    WHEN("the CPU executes a 5XY0 opcode on matching registers") {
      cpu.execute(0x5020);
      const auto pc1 = cpu.getPc();

      cpu.execute(0x5F30);
      const auto pc2 = cpu.getPc();

      THEN("the CPUs program counter is updated") {
        REQUIRE(pc1 == pc0 + Chip8::INSTRUCTION_BYTE_SIZE);
        REQUIRE(pc2 == pc0 + 2 * Chip8::INSTRUCTION_BYTE_SIZE);
      }
    }
    AND_WHEN("the CPU executes a 5XY0 opcode on non-matching registers") {
      cpu.execute(0x5080);
      const auto pc1 = cpu.getPc();

      cpu.execute(0x5F90);
      const auto pc2 = cpu.getPc();

      THEN("the CPUs program counter is remains unchanged") {
        REQUIRE(pc1 == pc0);
        REQUIRE(pc2 == pc0);
      }
    }
  }
}

SCENARIO("CPUs can skip instructions if a register differs from another", "[conditional]") {
  GIVEN("A CPU with some initialized registers") {
    Aux::TestKit testKit;
    CPU& cpu = testKit.cpu;
    cpu.writeRegister(Chip8::Register::VA, 0xA1);
    cpu.writeRegister(Chip8::Register::VB, 0xB2);
    cpu.writeRegister(Chip8::Register::VC, 0xC3);
    cpu.writeRegister(Chip8::Register::VD, 0xC3);
    cpu.writeRegister(Chip8::Register::VE, 0xB2);
    cpu.writeRegister(Chip8::Register::VF, 0xA1);
    const auto pc0 = cpu.getPc();

    WHEN("the CPU executes a 9XY0 opcode on non-matching registers") {
      cpu.execute(0x9AD0);
      const auto pc1 = cpu.getPc();

      cpu.execute(0x9BF0);
      const auto pc2 = cpu.getPc();

      THEN("the CPUs program counter is updated") {
        REQUIRE(pc1 == pc0 + Chip8::INSTRUCTION_BYTE_SIZE);
        REQUIRE(pc2 == pc0 + 2 * Chip8::INSTRUCTION_BYTE_SIZE);
      }
    }
    AND_WHEN("the CPU executes a 9XY0 opcode on matching registers") {
      cpu.execute(0x9CD0);
      const auto pc1 = cpu.getPc();

      cpu.execute(0x9EB0);
      const auto pc2 = cpu.getPc();

      THEN("the CPUs program counter is remains unchanged") {
        REQUIRE(pc1 == pc0);
        REQUIRE(pc2 == pc0);
      }
    }
  }
}

} // unnamed namespace