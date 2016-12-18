#include <catch.hpp>

#include "Chip8.hpp"
#include "CPU.hpp"

namespace {

using namespace Core8;

SCENARIO("CPUs can execute unconditional jumps", "[flow]") {
  GIVEN("A CPU") {
    CPU cpu{};

    WHEN("the CPU executes an 1NNN operation") {
      cpu.setInstruction(0x1ABC);
      cpu.decode();
      cpu.execute();
      const auto pc1 = cpu.getPc();

      cpu.setInstruction(0x10D2);
      cpu.decode();
      cpu.execute();
      const auto pc2 = cpu.getPc();

      THEN("the program counter is updated to the value of NNN") {
        REQUIRE(pc1 == 0xABC);
        REQUIRE(pc2 == 0x0D2);
      }
    }
  }
}

SCENARIO("CPUs can call subroutines", "[flow]") {
  GIVEN("A CPU") {
    CPU cpu{};

    WHEN("the CPU calls a subroutine executing an 2NNN operation") {
      const auto pc = cpu.getPc();
      const auto sp = cpu.getSp();

      cpu.setInstruction(0x2656);
      cpu.decode();
      cpu.execute();

      THEN("the program counter is pushed to the call stack") {
        REQUIRE(cpu.getStack().at(sp) == pc);
      }
      AND_THEN("the stack pointer is incremented") {
        REQUIRE(cpu.getSp() == sp + 1);
      }
      AND_THEN("the program counter is updated to the value of NNN") {
        REQUIRE(cpu.getPc() == 0x656);
      }
    }
  }
}

SCENARIO("CPUs can return from subroutines", "[flow]") {
  GIVEN("A CPU executing a subroutine") {
    CPU cpu{};
    cpu.setInstruction(0x2ABC);
    cpu.decode();
    cpu.execute();

    const auto sp = cpu.getSp();
    const auto stackTop = cpu.getStack().at(sp - 1u);

    WHEN("the CPU executes a 00EE operation to return from a subroutine") {
      cpu.setInstruction(0x00EE);
      cpu.decode();
      cpu.execute();

      THEN("the call stack topmost value is assigned to the program counter") {
        REQUIRE(cpu.getPc() == stackTop);
      }
      AND_THEN("the stack pointer is decremented") {
        REQUIRE(cpu.getSp() == sp - 1);
      }
    }
  }
}

} // unnamed namespace