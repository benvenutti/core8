#include <catch.hpp>

#include "aux/Aux.hpp"
#include "Chip8.hpp"
#include "CPU.hpp"

namespace {

using namespace Core8;

SCENARIO("CPUs can execute OR operations on registers", "[bitwise]") {
  GIVEN("A CPU with some initialized registers") {
    Aux::TestKit testKit;
    CPU& cpu = testKit.cpu;
    cpu.writeRegister(Chip8::Register::V0, 0b00001000);
    cpu.writeRegister(Chip8::Register::V6, 0b01010101);
    cpu.writeRegister(Chip8::Register::VA, 0b00001111);
    cpu.writeRegister(Chip8::Register::VE, 0b11001100);

    WHEN("the CPU executes an OR operation") {
      cpu.setInstruction(0x8061);
      cpu.decode();
      cpu.execute();
      cpu.setInstruction(0x8AE1);
      cpu.decode();
      cpu.execute();

      THEN("the target register holds the result of the OR operation") {
        REQUIRE(cpu.readRegister(Chip8::Register::V0) == 0b01011101);
        REQUIRE(cpu.readRegister(Chip8::Register::VA) == 0b11001111);
      }
      AND_THEN("the source register remains unchanged") {
        REQUIRE(cpu.readRegister(Chip8::Register::V6) == 0b01010101);
        REQUIRE(cpu.readRegister(Chip8::Register::VE) == 0b11001100);
      }
    }
  }
}

SCENARIO("CPUs can execute AND operations on registers", "[bitwise]") {
  GIVEN("A CPU with some initialized registers") {
    Aux::TestKit testKit;
    CPU& cpu = testKit.cpu;
    cpu.writeRegister(Chip8::Register::V1, 0b01011000);
    cpu.writeRegister(Chip8::Register::V7, 0b01010101);
    cpu.writeRegister(Chip8::Register::VB, 0b00001111);
    cpu.writeRegister(Chip8::Register::VF, 0b11001100);

    WHEN("the CPU executes an AND operation") {
      cpu.setInstruction(0x8172);
      cpu.decode();
      cpu.execute();
      cpu.setInstruction(0x8BF2);
      cpu.decode();
      cpu.execute();

      THEN("the target register holds the result of the AND operation") {
        REQUIRE(cpu.readRegister(Chip8::Register::V1) == 0b01010000);
        REQUIRE(cpu.readRegister(Chip8::Register::VB) == 0b00001100);
      }
      AND_THEN("the source register remains unchanged") {
        REQUIRE(cpu.readRegister(Chip8::Register::V7) == 0b01010101);
        REQUIRE(cpu.readRegister(Chip8::Register::VF) == 0b11001100);
      }
    }
  }
}

SCENARIO("CPUs can execute XOR operations on registers", "[bitwise]") {
  GIVEN("A CPU with some initialized registers") {
    Aux::TestKit testKit;
    CPU& cpu = testKit.cpu;
    cpu.writeRegister(Chip8::Register::V2, 0b01011000);
    cpu.writeRegister(Chip8::Register::V8, 0b01010101);
    cpu.writeRegister(Chip8::Register::VC, 0b00001111);
    cpu.writeRegister(Chip8::Register::VD, 0b11001100);

    WHEN("the CPU executes a XOR operation") {
      cpu.setInstruction(0x8283);
      cpu.decode();
      cpu.execute();
      cpu.setInstruction(0x8CD3);
      cpu.decode();
      cpu.execute();

      THEN("the target register holds the result of the XOR operation") {
        REQUIRE(cpu.readRegister(Chip8::Register::V2) == 0b00001101);
        REQUIRE(cpu.readRegister(Chip8::Register::VC) == 0b11000011);
      }
      AND_THEN("the source register remains unchanged") {
        REQUIRE(cpu.readRegister(Chip8::Register::V8) == 0b01010101);
        REQUIRE(cpu.readRegister(Chip8::Register::VD) == 0b11001100);
      }
    }
  }
}

SCENARIO("CPUs can shift registers right by one", "[bitwise]") {
  GIVEN("A CPU with some initialized registers") {
    Aux::TestKit testKit;
    CPU& cpu = testKit.cpu;
    cpu.writeRegister(Chip8::Register::V4, 0b01011000);
    cpu.writeRegister(Chip8::Register::VD, 0b01010101);

    WHEN("the CPU shifts a register right by one") {
      cpu.setInstruction(0x8406);
      cpu.decode();
      cpu.execute();
      const auto registerVf1 = cpu.readRegister(Chip8::Register::VF);

      cpu.setInstruction(0x8D06);
      cpu.decode();
      cpu.execute();
      const auto registerVf2 = cpu.readRegister(Chip8::Register::VF);

      THEN("the target register is shifted right by one") {
        REQUIRE(cpu.readRegister(Chip8::Register::V4) == 0b00101100);
        REQUIRE(cpu.readRegister(Chip8::Register::VD) == 0b00101010);
      }
      AND_THEN("VF is set to the value of the LSB of the target register before the shift") {
        REQUIRE(registerVf1 == 0b0);
        REQUIRE(registerVf2 == 0b1);
      }
    }
  }
}

SCENARIO("CPUs can shift registers left by one", "[bitwise]") {
  GIVEN("A CPU with some initialized registers") {
    Aux::TestKit testKit;
    CPU& cpu = testKit.cpu;
    cpu.writeRegister(Chip8::Register::VC, 0b11111111);
    cpu.writeRegister(Chip8::Register::VD, 0b01010101);

    WHEN("the CPU shifts a register left by one") {
      cpu.setInstruction(0x8C0E);
      cpu.decode();
      cpu.execute();
      const auto registerVf1 = cpu.readRegister(Chip8::Register::VF);

      cpu.setInstruction(0x8D0E);
      cpu.decode();
      cpu.execute();
      const auto registerVf2 = cpu.readRegister(Chip8::Register::VF);

      THEN("the target register is shifted left by one") {
        REQUIRE(cpu.readRegister(Chip8::Register::VC) == 0b11111110);
        REQUIRE(cpu.readRegister(Chip8::Register::VD) == 0b10101010);
      }
      AND_THEN("VF is set to the value of the MSB of the target register before the shift") {
        REQUIRE(registerVf1 == 0b1);
        REQUIRE(registerVf2 == 0b0);
      }
    }
  }
}

} // unnamed namespace