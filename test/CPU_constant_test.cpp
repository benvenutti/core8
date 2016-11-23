#include <catch.hpp>

#include "Chip8.hpp"
#include "CPU.hpp"

namespace {

using namespace Core8;

SCENARIO("CPUs can load constants to registers", "[constant]") {
  GIVEN("A CPU") {
    CPU cpu{};

    WHEN("the CPU executes a load constant operation to a register") {
      cpu.setInstruction(0x6001);
      cpu.execute();
      cpu.setInstruction(0x693A);
      cpu.execute();
      cpu.setInstruction(0x6FFF);
      cpu.execute();

      THEN("that register holds the loaded constant") {
        REQUIRE(cpu.readRegister(Chip8::REGISTER::V0) == 0x1);
        REQUIRE(cpu.readRegister(Chip8::REGISTER::V9) == 0x3A);
        REQUIRE(cpu.readRegister(Chip8::REGISTER::VF) == 0xFF);
      }
    }
  }
}

} // unnamed namespace