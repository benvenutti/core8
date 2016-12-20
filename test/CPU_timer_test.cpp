#include <catch.hpp>

#include "Chip8.hpp"
#include "CPU.hpp"

namespace {

SCENARIO("CPUs can assign the value of the delay timer to a register", "[timer]") {
  GIVEN("A CPU with an initialized delay timer") {
    Core8::CPU cpu{};
    cpu.setDelayTimer(0x3C);

    WHEN("the CPU executes a FX07 operation") {
      cpu.setInstruction(0xF007);
      cpu.decode();
      cpu.execute();
      cpu.setInstruction(0xFE07);
      cpu.decode();
      cpu.execute();

      THEN("the target register holds a copy of the delay timer value") {
        const auto delay = cpu.getDelayTimer();
        REQUIRE(cpu.readRegister(Core8::Chip8::REGISTER::V0) == delay);
        REQUIRE(cpu.readRegister(Core8::Chip8::REGISTER::VE) == delay);
      }
    }
  }
}

} // unnamed namespace
