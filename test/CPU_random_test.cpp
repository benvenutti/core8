#include <catch.hpp>

#include "aux/Aux.hpp"
#include "Chip8.hpp"
#include "CPU.hpp"

namespace {

struct CpuFixture {
  Aux::TestKit testKit;
  Core8::MMU& mmu = testKit.mmu;
  Core8::CPU& cpu = testKit.cpu;
  Aux::RandomNumberGeneratorMock& rndGenerator = testKit.rndGenerator;
};

SCENARIO_METHOD(
    CpuFixture,
    "CPU sets register X to the result of a bitwise AND operation on "
        "the minimum possible random number generated and NN "
        "using the CXNN opcode"
    "[memory]"
) {
  GIVEN("A CPU and the random generated value 0") {
    rndGenerator.setValue(0x0);

    WHEN("the CPU executes a CXNN operation with X equal to 0 and NN equal to FF") {
      cpu.execute(0xC0FF);

      THEN("register V0 is set to 0") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::V0) == 0x0);
      }
    }
  }
}

SCENARIO_METHOD(
    CpuFixture,
    "CPU sets register X to the result of a bitwise AND operation on "
        "the maximum possible random number generated and NN "
        "using the CXNN opcode"
        "[memory]"
) {
  GIVEN("A CPU and the random generated value FF") {
    rndGenerator.setValue(0xFF);

    WHEN("the CPU executes a CXNN operation with X equal to F and NN equal to FF") {
      cpu.execute(0xCFFF);

      THEN("register VF is set to FF") {
        REQUIRE(cpu.readRegister(Core8::Chip8::Register::VF) == 0xFF);
      }
    }
  }
}

} // namespace
