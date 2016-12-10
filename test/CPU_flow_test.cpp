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

} // unnamed namespace