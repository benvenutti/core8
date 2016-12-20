#include <catch.hpp>

#include "Chip8.hpp"
#include "CPU.hpp"

namespace {

SCENARIO("CPUs can load addresses to the address register I", "[memory]") {
  GIVEN("A CPU") {
    Core8::CPU cpu{};

    WHEN("the CPU executes a ANNN operation") {
      cpu.setInstruction(0xA123);
      cpu.decode();
      cpu.execute();
      const auto address1 = cpu.getI();

      cpu.setInstruction(0xAFFF);
      cpu.decode();
      cpu.execute();
      const auto address2 = cpu.getI();

      THEN("the address NNN is loaded into the address register I") {
        REQUIRE(0x123 == address1);
        REQUIRE(0xFFF == address2);
      }
    }
  }
}

} // unnamed namespace