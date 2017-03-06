#include <catch.hpp>

#include "aux/Aux.hpp"
#include "Chip8.hpp"
#include "CPU.hpp"

namespace {

SCENARIO(
    "Operation FX33 stores in memory the BCD representation of the minimum value of VX",
    "[bcd]"
) {
  GIVEN("A CPU with V0 set to 0 and register I set to 100") {
    Aux::TestKit testKit;
    Core8::CPU& cpu = testKit.cpu;
    Core8::MMU& mmu = testKit.mmu;

    cpu.writeRegister(Core8::Chip8::Register::V0, 0x0);
    cpu.setI(100);

    WHEN("the CPU executes a FX33 operation with X equal to 0") {
      cpu.setInstruction(0xF033);
      cpu.decode();
      cpu.execute();

      THEN("the memory holds 3 digits with the BCD representation of VX starting at I") {
        REQUIRE(mmu.readByte(100u) == 0);
        REQUIRE(mmu.readByte(101u) == 0);
        REQUIRE(mmu.readByte(102u) == 0);
      }
    }
  }
}

SCENARIO(
    "Operation FX33 stores in memory the BCD representation of the maximum value of VX",
    "[bcd]"
) {
  GIVEN("A CPU with V0 set to 255 and register I set to 200") {
    Aux::TestKit testKit;
    Core8::CPU& cpu = testKit.cpu;
    Core8::MMU& mmu = testKit.mmu;

    cpu.writeRegister(Core8::Chip8::Register::V0, 0xFF);
    cpu.setI(200);

    WHEN("the CPU executes a FX33 operation with X equal to 0") {
      cpu.setInstruction(0xF033);
      cpu.decode();
      cpu.execute();

      THEN("the memory holds 3 digits with the BCD representation of VX starting at I") {
        REQUIRE(mmu.readByte(200u) == 2);
        REQUIRE(mmu.readByte(201u) == 5);
        REQUIRE(mmu.readByte(202u) == 5);
      }
    }
  }
}

} // unnamed namespace