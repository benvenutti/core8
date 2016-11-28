#include <catch.hpp>

#include "Chip8.hpp"
#include "CPU.hpp"

namespace {

using namespace Core8;

SCENARIO("CPUs can execute OR operations on registers", "[bitwise]") {
  GIVEN("A CPU with some initialized registers") {
    CPU cpu{};
    cpu.writeRegister(Chip8::REGISTER::V0, 0b00001000);
    cpu.writeRegister(Chip8::REGISTER::V6, 0b01010101);
    cpu.writeRegister(Chip8::REGISTER::VA, 0b00001111);
    cpu.writeRegister(Chip8::REGISTER::VE, 0b11001100);

    WHEN("the CPU executes an OR operation") {
      cpu.setInstruction(0x8061);
      cpu.decode();
      cpu.execute();
      cpu.setInstruction(0x8AE1);
      cpu.decode();
      cpu.execute();

      THEN("the target register holds the result of the OR operation") {
        REQUIRE(cpu.readRegister(Chip8::REGISTER::V0) == 0b01011101);
        REQUIRE(cpu.readRegister(Chip8::REGISTER::VA) == 0b11001111);
      }
      AND_THEN("the source register remains unchanged") {
        REQUIRE(cpu.readRegister(Chip8::REGISTER::V6) == 0b01010101);
        REQUIRE(cpu.readRegister(Chip8::REGISTER::VE) == 0b11001100);
      }
    }
  }
}

} // unnamed namespace