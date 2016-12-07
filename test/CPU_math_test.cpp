#include <catch.hpp>

#include "Chip8.hpp"
#include "CPU.hpp"

namespace {

using namespace Core8;

SCENARIO("CPUs can add VY to VX", "[math]") {
  GIVEN("A CPU with some initialized registers") {
    CPU cpu{};
    cpu.writeRegister(Chip8::REGISTER::V1, 0x11);
    cpu.writeRegister(Chip8::REGISTER::V4, 0x35);
    cpu.writeRegister(Chip8::REGISTER::V5, 0xFE);

    WHEN("the CPU executes a 8XY4 operation on two registers without carry") {
      cpu.setInstruction(0x8144);
      cpu.decode();
      cpu.execute();

      THEN("the value of VY is added to VX") {
        REQUIRE(cpu.readRegister(Chip8::REGISTER::V1) == 0x46);
      }
      AND_THEN("VF is set to 0") {
        REQUIRE(cpu.readRegister(Chip8::REGISTER::VF) == 0x0);
      }
    }
    AND_WHEN("the CPU executes a 8XY4 operation on two registers with a carry") {
      cpu.setInstruction(0x8154);
      cpu.decode();
      cpu.execute();

      THEN("the value of VY is added to VX") {
        REQUIRE(cpu.readRegister(Chip8::REGISTER::V1) == 0xF);
      }
      AND_THEN("VF is set to 1") {
        REQUIRE(cpu.readRegister(Chip8::REGISTER::VF) == 0x1);
      }
    }
  }
}

} // unnamed namespace