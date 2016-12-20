#include <catch.hpp>

#include "aux/Aux.hpp"
#include "Chip8.hpp"
#include "CPU.hpp"

namespace {

using namespace Core8;

SCENARIO("CPUs can add VY from VX", "[math]") {
  GIVEN("A CPU with some initialized registers") {
    Aux::TestKit testKit;
    CPU& cpu = testKit.cpu;
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

SCENARIO("CPUs can subtract VY from VX", "[math]") {
  GIVEN("A CPU with some initialized registers") {
    Aux::TestKit testKit;
    CPU& cpu = testKit.cpu;
    cpu.writeRegister(Chip8::REGISTER::VA, 0xA3);
    cpu.writeRegister(Chip8::REGISTER::VB, 0x15);
    cpu.writeRegister(Chip8::REGISTER::VC, 0xFF);

    WHEN("the CPU executes a 8XY5 operation on two registers without a borrow") {
      cpu.setInstruction(0x8AB5);
      cpu.decode();
      cpu.execute();

      THEN("the value of VY is subtracted from VX") {
        REQUIRE(cpu.readRegister(Chip8::REGISTER::VA) == 0x8E);
      }
      AND_THEN("VF is set to 1") {
        REQUIRE(cpu.readRegister(Chip8::REGISTER::VF) == 0x1);
      }
    }
    AND_WHEN("the CPU executes a 8XY5 operation on two registers with a borrow") {
      cpu.setInstruction(0x8AC5);
      cpu.decode();
      cpu.execute();

      THEN("the value of VY is subtracted from VX") {
        REQUIRE(cpu.readRegister(Chip8::REGISTER::VA) == 0xa4);
      }
      AND_THEN("VF is set to 0") {
        REQUIRE(cpu.readRegister(Chip8::REGISTER::VF) == 0x0);
      }
    }
  }
}

SCENARIO("CPUs can subtract VX to VY", "[math]") {
  GIVEN("A CPU with some initialized registers") {
    Aux::TestKit testKit;
    CPU& cpu = testKit.cpu;
    cpu.writeRegister(Chip8::REGISTER::V3, 0x3F);
    cpu.writeRegister(Chip8::REGISTER::V4, 0xBB);
    cpu.writeRegister(Chip8::REGISTER::V5, 0xFF);

    WHEN("a 8XY7 operation is executed on two registers without a borrow") {
      cpu.setInstruction(0x8347);
      cpu.decode();
      cpu.execute();

      THEN("VX is set to the value of VY minus VX") {
        REQUIRE(cpu.readRegister(Chip8::REGISTER::V3) == 0x7C);
      }
      AND_THEN("VF is set to 1") {
        REQUIRE(cpu.readRegister(Chip8::REGISTER::VF) == 0x1);
      }
    }
    AND_WHEN("a 8XY7 operation is executed on two registers with a borrow") {
      cpu.setInstruction(0x8547);
      cpu.decode();
      cpu.execute();

      THEN("VX is set to the value of VY minus VX") {
        REQUIRE(cpu.readRegister(Chip8::REGISTER::V5) == 0xBC);
      }
      AND_THEN("VF is set to 0") {
        REQUIRE(cpu.readRegister(Chip8::REGISTER::VF) == 0x0);
      }
    }
  }
}

} // unnamed namespace