#include <catch.hpp>

#include "aux/Aux.hpp"
#include "Chip8.hpp"
#include "CPU.hpp"

namespace {

using namespace Core8;

SCENARIO("CPUs can execute unconditional jumps", "[flow]") {
  GIVEN("A CPU") {
    Aux::TestKit testKit;
    CPU& cpu = testKit.cpu;

    WHEN("the CPU executes an 1NNN operation") {
      cpu.execute(0x1ABC);
      const auto pc1 = cpu.getPc();

      cpu.execute(0x10D2);
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
    Aux::TestKit testKit;
    CPU& cpu = testKit.cpu;

    WHEN("the CPU calls a subroutine executing an 2NNN operation") {
      const auto pc = cpu.getPc();
      const auto sp = cpu.getSp();

      cpu.execute(0x2656);

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
    Aux::TestKit testKit;
    CPU& cpu = testKit.cpu;
    cpu.execute(0x2ABC);

    const auto sp = cpu.getSp();
    const auto stackTop = cpu.getStack().at(sp - 1u);

    WHEN("the CPU executes a 00EE operation to return from a subroutine") {
      cpu.execute(0x00EE);

      THEN("the call stack topmost value is assigned to the program counter") {
        REQUIRE(cpu.getPc() == stackTop);
      }
      AND_THEN("the stack pointer is decremented") {
        REQUIRE(cpu.getSp() == sp - 1);
      }
    }
  }
}

SCENARIO("CPUs can execute unconditional jumps using register V0", "[flow]") {
  GIVEN("A CPU with initialized registers") {
    Aux::TestKit testKit;
    CPU& cpu = testKit.cpu;
    cpu.writeRegister(Chip8::Register::V0, 0x2D);

    WHEN("the CPU executes an BNNN operation") {
      cpu.execute(0xB131);

      THEN("the program counter is updated to the value of NNN plus V0") {
        REQUIRE(cpu.getPc() == 0x15E);
      }
    }
  }
}

} // unnamed namespace