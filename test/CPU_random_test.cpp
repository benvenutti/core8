#include <catch.hpp>

#include "aux/Aux.hpp"
#include "Chip8.hpp"
#include "CPU.hpp"

namespace {

SCENARIO(
    "Operation CXNN sets VX to the result of NN and (bitwise) the minimum possible random number",
    "[random]"
) {
  GIVEN("A CPU and the random generated value 0") {
    Aux::TestKit testKit;
    Core8::CPU& cpu = testKit.cpu;
    Aux::RandomNumberGeneratorMock& rng = testKit.rndGenerator;
    rng.setValue(0x0);

    WHEN("the CPU executes a CXNN operation with X equal to 0 and NN equal to FF") {
      cpu.setInstruction(0xC0FF);
      cpu.decode();
      cpu.execute();

      THEN("register V0 is set to 0") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::V0) == 0x0);
      }
    }
  }
}

SCENARIO(
    "Operation CXNN sets VX to the result of NN and (bitwise) the maximum possible random number",
    "[random]"
) {
  GIVEN("A CPU and the random generated value FF") {
    Aux::TestKit testKit;
    Core8::CPU& cpu = testKit.cpu;
    Aux::RandomNumberGeneratorMock& rng = testKit.rndGenerator;
    rng.setValue(0xFF);

    WHEN("the CPU executes a CXNN operation with X equal to F and NN equal to FF") {
      cpu.setInstruction(0xCFFF);
      cpu.decode();
      cpu.execute();

      THEN("register VF is set to FF") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::VF) == 0xFF);
      }
    }
  }
}

} // unnamed namespace
