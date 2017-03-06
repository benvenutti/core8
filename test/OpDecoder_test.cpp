#include <catch.hpp>

#include "OpDecoder.hpp"

namespace {

using namespace Core8;

TEST_CASE("Display opcodes are decoded", "[display]") {
  REQUIRE(OpDecoder::decode(0x00E0) == Chip8::OpCode::CLEAR_SCREEN);

  REQUIRE(OpDecoder::decode(0xD000) == Chip8::OpCode::DRAW);
  REQUIRE(OpDecoder::decode(0xDFFF) == Chip8::OpCode::DRAW);
}

TEST_CASE("Flow opcodes are decoded", "[flow]") {
  REQUIRE(OpDecoder::decode(0x00EE) == Chip8::OpCode::RETURN);

  REQUIRE(OpDecoder::decode(0x1000) == Chip8::OpCode::JUMP);
  REQUIRE(OpDecoder::decode(0x1FFF) == Chip8::OpCode::JUMP);

  REQUIRE(OpDecoder::decode(0x2000) == Chip8::OpCode::CALL);
  REQUIRE(OpDecoder::decode(0x2FFF) == Chip8::OpCode::CALL);

  REQUIRE(OpDecoder::decode(0xB000) == Chip8::OpCode::JUMP_NNN_PLUS_V0);
  REQUIRE(OpDecoder::decode(0xBFFF) == Chip8::OpCode::JUMP_NNN_PLUS_V0);
}

TEST_CASE("Conditional opcodes are decoded", "[conditional]") {
  REQUIRE(OpDecoder::decode(0x3000) == Chip8::OpCode::SKIP_IF_VX_EQUALS_NN);
  REQUIRE(OpDecoder::decode(0x3FFF) == Chip8::OpCode::SKIP_IF_VX_EQUALS_NN);

  REQUIRE(OpDecoder::decode(0x4000) == Chip8::OpCode::SKIP_IF_VX_NOT_EQUALS_NN);
  REQUIRE(OpDecoder::decode(0x4FFF) == Chip8::OpCode::SKIP_IF_VX_NOT_EQUALS_NN);

  REQUIRE(OpDecoder::decode(0x5000) == Chip8::OpCode::SKIP_IF_VX_EQUALS_VY);
  REQUIRE(OpDecoder::decode(0x5FF0) == Chip8::OpCode::SKIP_IF_VX_EQUALS_VY);

  REQUIRE(OpDecoder::decode(0x9000) == Chip8::OpCode::SKIP_IF_VX_NOT_EQUALS_VY);
  REQUIRE(OpDecoder::decode(0x9FF0) == Chip8::OpCode::SKIP_IF_VX_NOT_EQUALS_VY);
}

TEST_CASE("Constant opcodes are decoded", "[constant]") {
  REQUIRE(OpDecoder::decode(0x6000) == Chip8::OpCode::LOAD_NN_TO_VX);
  REQUIRE(OpDecoder::decode(0x6FFF) == Chip8::OpCode::LOAD_NN_TO_VX);

  REQUIRE(OpDecoder::decode(0x7000) == Chip8::OpCode::ADD_NN_TO_VX);
  REQUIRE(OpDecoder::decode(0x7FFF) == Chip8::OpCode::ADD_NN_TO_VX);
}

TEST_CASE("Assignment opcodes are decoded", "[assign]") {
  REQUIRE(OpDecoder::decode(0x8000) == Chip8::OpCode::LOAD_VY_TO_VX);
  REQUIRE(OpDecoder::decode(0x8FF0) == Chip8::OpCode::LOAD_VY_TO_VX);
  REQUIRE(OpDecoder::decode(0x8FFF) != Chip8::OpCode::LOAD_VY_TO_VX);
}

TEST_CASE("Bitwise operation opcodes are decoded", "[bitwise]") {
  REQUIRE(OpDecoder::decode(0x8001) == Chip8::OpCode::VX_OR_VY);
  REQUIRE(OpDecoder::decode(0x8FF1) == Chip8::OpCode::VX_OR_VY);

  REQUIRE(OpDecoder::decode(0x8002) == Chip8::OpCode::VX_AND_VY);
  REQUIRE(OpDecoder::decode(0x8FF2) == Chip8::OpCode::VX_AND_VY);

  REQUIRE(OpDecoder::decode(0x8003) == Chip8::OpCode::VX_XOR_VY);
  REQUIRE(OpDecoder::decode(0x8FF3) == Chip8::OpCode::VX_XOR_VY);

  REQUIRE(OpDecoder::decode(0x8006) == Chip8::OpCode::SHIFT_VX_RIGHT);
  REQUIRE(OpDecoder::decode(0x8FF6) == Chip8::OpCode::SHIFT_VX_RIGHT);

  REQUIRE(OpDecoder::decode(0x800E) == Chip8::OpCode::SHIFT_VX_LEFT);
  REQUIRE(OpDecoder::decode(0x8FFE) == Chip8::OpCode::SHIFT_VX_LEFT);
}

TEST_CASE("Mathematical opcodes are decoded", "[math]") {
  REQUIRE(OpDecoder::decode(0x8004) == Chip8::OpCode::VX_PLUS_VY);
  REQUIRE(OpDecoder::decode(0x8FF4) == Chip8::OpCode::VX_PLUS_VY);

  REQUIRE(OpDecoder::decode(0x8005) == Chip8::OpCode::VX_MINUS_VY);
  REQUIRE(OpDecoder::decode(0x8FF5) == Chip8::OpCode::VX_MINUS_VY);

  REQUIRE(OpDecoder::decode(0x8007) == Chip8::OpCode::SET_VX_TO_VY_MINUS_VX);
  REQUIRE(OpDecoder::decode(0x8FF7) == Chip8::OpCode::SET_VX_TO_VY_MINUS_VX);
}

TEST_CASE("Memory access opcodes are decoded", "[memory]") {
  REQUIRE(OpDecoder::decode(0xA000) == Chip8::OpCode::LOAD_NNN_TO_I);
  REQUIRE(OpDecoder::decode(0xAFFF) == Chip8::OpCode::LOAD_NNN_TO_I);

  REQUIRE(OpDecoder::decode(0xF01E) == Chip8::OpCode::ADD_VX_TO_I);
  REQUIRE(OpDecoder::decode(0xFF1E) == Chip8::OpCode::ADD_VX_TO_I);

  REQUIRE(OpDecoder::decode(0xF029) == Chip8::OpCode::LOAD_FONT_SPRITE_ADDRESS_TO_I);
  REQUIRE(OpDecoder::decode(0xFF29) == Chip8::OpCode::LOAD_FONT_SPRITE_ADDRESS_TO_I);

  REQUIRE(OpDecoder::decode(0xF055) == Chip8::OpCode::LOAD_V0_TO_VX_IN_ADDRESS_I);
  REQUIRE(OpDecoder::decode(0xFF55) == Chip8::OpCode::LOAD_V0_TO_VX_IN_ADDRESS_I);

  REQUIRE(OpDecoder::decode(0xF065) == Chip8::OpCode::LOAD_ADDRESS_I_TO_V0_TO_VX);
  REQUIRE(OpDecoder::decode(0xFF65) == Chip8::OpCode::LOAD_ADDRESS_I_TO_V0_TO_VX);
}

TEST_CASE("Random number generation opcodes are decoded", "[random]") {
  REQUIRE(OpDecoder::decode(0xC000) == Chip8::OpCode::LOAD_RANDOM_TO_VX);
  REQUIRE(OpDecoder::decode(0xCFFF) == Chip8::OpCode::LOAD_RANDOM_TO_VX);
}

TEST_CASE("Keypad opcodes are decoded", "[keypad]") {
  REQUIRE(OpDecoder::decode(0xE09E) == Chip8::OpCode::SKIP_IF_VX_IS_PRESSED);
  REQUIRE(OpDecoder::decode(0xEF9E) == Chip8::OpCode::SKIP_IF_VX_IS_PRESSED);

  REQUIRE(OpDecoder::decode(0xE0A1) == Chip8::OpCode::SKIP_IF_VX_IS_NOT_PRESSED);
  REQUIRE(OpDecoder::decode(0xEFA1) == Chip8::OpCode::SKIP_IF_VX_IS_NOT_PRESSED);

  REQUIRE(OpDecoder::decode(0xF00A) == Chip8::OpCode::LOAD_PRESSED_KEY_TO_VX);
  REQUIRE(OpDecoder::decode(0xFF0A) == Chip8::OpCode::LOAD_PRESSED_KEY_TO_VX);
}

TEST_CASE("Timer opcodes are decoded", "[timer]") {
  REQUIRE(OpDecoder::decode(0xF007) == Chip8::OpCode::LOAD_DELAY_TIMER_TO_VX);
  REQUIRE(OpDecoder::decode(0xFF07) == Chip8::OpCode::LOAD_DELAY_TIMER_TO_VX);

  REQUIRE(OpDecoder::decode(0xF015) == Chip8::OpCode::LOAD_VX_TO_DELAY_TIMER);
  REQUIRE(OpDecoder::decode(0xFF15) == Chip8::OpCode::LOAD_VX_TO_DELAY_TIMER);
}

TEST_CASE("Sound opcodes are decoded", "[sound]") {
  REQUIRE(OpDecoder::decode(0xF018) == Chip8::OpCode::LOAD_VX_TO_SOUND_TIMER);
  REQUIRE(OpDecoder::decode(0xFF18) == Chip8::OpCode::LOAD_VX_TO_SOUND_TIMER);
}

TEST_CASE("Binary-coded decimal opcodes are decoded", "[bcd]") {
  REQUIRE(OpDecoder::decode(0xF033) == Chip8::OpCode::LOAD_VX_BCD_TO_I);
  REQUIRE(OpDecoder::decode(0xFF33) == Chip8::OpCode::LOAD_VX_BCD_TO_I);
}

} // namespace