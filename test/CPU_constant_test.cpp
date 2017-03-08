#include <catch.hpp>

#include "aux/Aux.hpp"
#include "Chip8.hpp"
#include "CPU.hpp"

namespace {

using namespace Core8;

SCENARIO("CPUs can load constants to registers", "[constant]") {
  GIVEN("A CPU") {
    Aux::TestKit testKit;
    CPU& cpu = testKit.cpu;

    WHEN("the CPU executes a load constant operation to a register") {
      cpu.execute(0x6001);
      cpu.execute(0x693A);
      cpu.execute(0x6FFF);

      THEN("that register holds the loaded constant") {
        REQUIRE(cpu.readRegister(Chip8::Register::V0) == 0x1);
        REQUIRE(cpu.readRegister(Chip8::Register::V9) == 0x3A);
        REQUIRE(cpu.readRegister(Chip8::Register::VF) == 0xFF);
      }
    }
  }
}

SCENARIO("CPUs can add constants to registers", "[constant]") {
  GIVEN("A CPU with initialized registers") {
    Aux::TestKit testKit;
    CPU& cpu = testKit.cpu;
    cpu.writeRegister(Chip8::Register::V3, 0x03);
    cpu.writeRegister(Chip8::Register::V7, 0x34);
    cpu.writeRegister(Chip8::Register::VF, 0xFE);

    WHEN("the CPU executes an add constant operation to a register") {
      cpu.execute(0x7301);
      cpu.execute(0x7793);
      cpu.execute(0x7F01);

      THEN("that register holds the value of the sum") {
        REQUIRE(cpu.readRegister(Chip8::Register::V3) == 0x4);
        REQUIRE(cpu.readRegister(Chip8::Register::V7) == 0xC7);
        REQUIRE(cpu.readRegister(Chip8::Register::VF) == 0xFF);
      }
    }
  }
}

} // unnamed namespace