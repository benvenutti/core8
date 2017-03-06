#include <catch.hpp>

#include "aux/Aux.hpp"
#include "Chip8.hpp"
#include "CPU.hpp"

namespace {

using namespace Core8;

SCENARIO("CPUs can assign the value of one register to another", "[assign]") {
  GIVEN("A CPU with some initialized registers") {
    Aux::TestKit testKit;
    CPU& cpu = testKit.cpu;
    cpu.writeRegister(Chip8::Register::V0, 0x01);
    cpu.writeRegister(Chip8::Register::VC, 0xCB);
    cpu.writeRegister(Chip8::Register::VF, 0xFF);

    WHEN("the CPU assigns one register to another") {
      cpu.setInstruction(0x8100);
      cpu.decode();
      cpu.execute();
      cpu.setInstruction(0x8DC0);
      cpu.decode();
      cpu.execute();
      cpu.setInstruction(0x8EF0);
      cpu.decode();
      cpu.execute();

      THEN("the target register holds a copy of the source register") {
        REQUIRE(cpu.readRegister(Chip8::Register::V1) == 0x01);
        REQUIRE(cpu.readRegister(Chip8::Register::VD) == 0xCB);
        REQUIRE(cpu.readRegister(Chip8::Register::VE) == 0xFF);
      }
      AND_THEN("the source register remains unchanged") {
        REQUIRE(cpu.readRegister(Chip8::Register::V0) == 0x01);
        REQUIRE(cpu.readRegister(Chip8::Register::VC) == 0xCB);
        REQUIRE(cpu.readRegister(Chip8::Register::VF) == 0xFF);
      }
    }
  }
}

} // unnamed namespace