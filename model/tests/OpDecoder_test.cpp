#include <catch.hpp>

#include "OpDecoder.hpp"

namespace
{

using namespace model;

TEST_CASE( "Display opcodes are decoded", "[display]" )
{
    REQUIRE( OpDecoder::decode( 0x00E0 ) == chip8::opcode::CLEAR_SCREEN );

    REQUIRE( OpDecoder::decode( 0xD000 ) == chip8::opcode::DRAW );
    REQUIRE( OpDecoder::decode( 0xDFFF ) == chip8::opcode::DRAW );
}

TEST_CASE( "Flow opcodes are decoded", "[flow]" )
{
    REQUIRE( OpDecoder::decode( 0x00EE ) == chip8::opcode::RETURN );

    REQUIRE( OpDecoder::decode( 0x1000 ) == chip8::opcode::JUMP );
    REQUIRE( OpDecoder::decode( 0x1FFF ) == chip8::opcode::JUMP );

    REQUIRE( OpDecoder::decode( 0x2000 ) == chip8::opcode::CALL );
    REQUIRE( OpDecoder::decode( 0x2FFF ) == chip8::opcode::CALL );

    REQUIRE( OpDecoder::decode( 0xB000 ) == chip8::opcode::JUMP_NNN_PLUS_V0 );
    REQUIRE( OpDecoder::decode( 0xBFFF ) == chip8::opcode::JUMP_NNN_PLUS_V0 );
}

TEST_CASE( "Conditional opcodes are decoded", "[conditional]" )
{
    REQUIRE( OpDecoder::decode( 0x3000 ) == chip8::opcode::SKIP_IF_VX_EQUALS_NN );
    REQUIRE( OpDecoder::decode( 0x3FFF ) == chip8::opcode::SKIP_IF_VX_EQUALS_NN );

    REQUIRE( OpDecoder::decode( 0x4000 ) == chip8::opcode::SKIP_IF_VX_NOT_EQUALS_NN );
    REQUIRE( OpDecoder::decode( 0x4FFF ) == chip8::opcode::SKIP_IF_VX_NOT_EQUALS_NN );

    REQUIRE( OpDecoder::decode( 0x5000 ) == chip8::opcode::SKIP_IF_VX_EQUALS_VY );
    REQUIRE( OpDecoder::decode( 0x5FF0 ) == chip8::opcode::SKIP_IF_VX_EQUALS_VY );

    REQUIRE( OpDecoder::decode( 0x9000 ) == chip8::opcode::SKIP_IF_VX_NOT_EQUALS_VY );
    REQUIRE( OpDecoder::decode( 0x9FF0 ) == chip8::opcode::SKIP_IF_VX_NOT_EQUALS_VY );
}

TEST_CASE( "Constant opcodes are decoded", "[constant]" )
{
    REQUIRE( OpDecoder::decode( 0x6000 ) == chip8::opcode::LOAD_NN_TO_VX );
    REQUIRE( OpDecoder::decode( 0x6FFF ) == chip8::opcode::LOAD_NN_TO_VX );

    REQUIRE( OpDecoder::decode( 0x7000 ) == chip8::opcode::ADD_NN_TO_VX );
    REQUIRE( OpDecoder::decode( 0x7FFF ) == chip8::opcode::ADD_NN_TO_VX );
}

TEST_CASE( "Assignment opcodes are decoded", "[assign]" )
{
    REQUIRE( OpDecoder::decode( 0x8000 ) == chip8::opcode::LOAD_VY_TO_VX );
    REQUIRE( OpDecoder::decode( 0x8FF0 ) == chip8::opcode::LOAD_VY_TO_VX );
    REQUIRE( OpDecoder::decode( 0x8FFF ) != chip8::opcode::LOAD_VY_TO_VX );
}

TEST_CASE( "Bitwise operation opcodes are decoded", "[bitwise]" )
{
    REQUIRE( OpDecoder::decode( 0x8001 ) == chip8::opcode::VX_OR_VY );
    REQUIRE( OpDecoder::decode( 0x8FF1 ) == chip8::opcode::VX_OR_VY );

    REQUIRE( OpDecoder::decode( 0x8002 ) == chip8::opcode::VX_AND_VY );
    REQUIRE( OpDecoder::decode( 0x8FF2 ) == chip8::opcode::VX_AND_VY );

    REQUIRE( OpDecoder::decode( 0x8003 ) == chip8::opcode::VX_XOR_VY );
    REQUIRE( OpDecoder::decode( 0x8FF3 ) == chip8::opcode::VX_XOR_VY );

    REQUIRE( OpDecoder::decode( 0x8006 ) == chip8::opcode::SHIFT_VX_RIGHT );
    REQUIRE( OpDecoder::decode( 0x8FF6 ) == chip8::opcode::SHIFT_VX_RIGHT );

    REQUIRE( OpDecoder::decode( 0x800E ) == chip8::opcode::SHIFT_VX_LEFT );
    REQUIRE( OpDecoder::decode( 0x8FFE ) == chip8::opcode::SHIFT_VX_LEFT );
}

TEST_CASE( "Mathematical opcodes are decoded", "[math]" )
{
    REQUIRE( OpDecoder::decode( 0x8004 ) == chip8::opcode::VX_PLUS_VY );
    REQUIRE( OpDecoder::decode( 0x8FF4 ) == chip8::opcode::VX_PLUS_VY );

    REQUIRE( OpDecoder::decode( 0x8005 ) == chip8::opcode::VX_MINUS_VY );
    REQUIRE( OpDecoder::decode( 0x8FF5 ) == chip8::opcode::VX_MINUS_VY );

    REQUIRE( OpDecoder::decode( 0x8007 ) == chip8::opcode::SET_VX_TO_VY_MINUS_VX );
    REQUIRE( OpDecoder::decode( 0x8FF7 ) == chip8::opcode::SET_VX_TO_VY_MINUS_VX );
}

TEST_CASE( "Memory access opcodes are decoded", "[memory]" )
{
    REQUIRE( OpDecoder::decode( 0xA000 ) == chip8::opcode::LOAD_NNN_TO_I );
    REQUIRE( OpDecoder::decode( 0xAFFF ) == chip8::opcode::LOAD_NNN_TO_I );

    REQUIRE( OpDecoder::decode( 0xF01E ) == chip8::opcode::ADD_VX_TO_I );
    REQUIRE( OpDecoder::decode( 0xFF1E ) == chip8::opcode::ADD_VX_TO_I );

    REQUIRE( OpDecoder::decode( 0xF029 ) == chip8::opcode::LOAD_FONT_SPRITE_ADDRESS_TO_I );
    REQUIRE( OpDecoder::decode( 0xFF29 ) == chip8::opcode::LOAD_FONT_SPRITE_ADDRESS_TO_I );

    REQUIRE( OpDecoder::decode( 0xF055 ) == chip8::opcode::LOAD_V0_TO_VX_IN_ADDRESS_I );
    REQUIRE( OpDecoder::decode( 0xFF55 ) == chip8::opcode::LOAD_V0_TO_VX_IN_ADDRESS_I );

    REQUIRE( OpDecoder::decode( 0xF065 ) == chip8::opcode::LOAD_ADDRESS_I_TO_V0_TO_VX );
    REQUIRE( OpDecoder::decode( 0xFF65 ) == chip8::opcode::LOAD_ADDRESS_I_TO_V0_TO_VX );
}

TEST_CASE( "Random number generation opcodes are decoded", "[random]" )
{
    REQUIRE( OpDecoder::decode( 0xC000 ) == chip8::opcode::LOAD_RANDOM_TO_VX );
    REQUIRE( OpDecoder::decode( 0xCFFF ) == chip8::opcode::LOAD_RANDOM_TO_VX );
}

TEST_CASE( "Keypad opcodes are decoded", "[keypad]" )
{
    REQUIRE( OpDecoder::decode( 0xE09E ) == chip8::opcode::SKIP_IF_VX_IS_PRESSED );
    REQUIRE( OpDecoder::decode( 0xEF9E ) == chip8::opcode::SKIP_IF_VX_IS_PRESSED );

    REQUIRE( OpDecoder::decode( 0xE0A1 ) == chip8::opcode::SKIP_IF_VX_IS_NOT_PRESSED );
    REQUIRE( OpDecoder::decode( 0xEFA1 ) == chip8::opcode::SKIP_IF_VX_IS_NOT_PRESSED );

    REQUIRE( OpDecoder::decode( 0xF00A ) == chip8::opcode::LOAD_PRESSED_KEY_TO_VX );
    REQUIRE( OpDecoder::decode( 0xFF0A ) == chip8::opcode::LOAD_PRESSED_KEY_TO_VX );
}

TEST_CASE( "Timer opcodes are decoded", "[timer]" )
{
    REQUIRE( OpDecoder::decode( 0xF007 ) == chip8::opcode::LOAD_DELAY_TIMER_TO_VX );
    REQUIRE( OpDecoder::decode( 0xFF07 ) == chip8::opcode::LOAD_DELAY_TIMER_TO_VX );

    REQUIRE( OpDecoder::decode( 0xF015 ) == chip8::opcode::LOAD_VX_TO_DELAY_TIMER );
    REQUIRE( OpDecoder::decode( 0xFF15 ) == chip8::opcode::LOAD_VX_TO_DELAY_TIMER );
}

TEST_CASE( "Sound opcodes are decoded", "[sound]" )
{
    REQUIRE( OpDecoder::decode( 0xF018 ) == chip8::opcode::LOAD_VX_TO_SOUND_TIMER );
    REQUIRE( OpDecoder::decode( 0xFF18 ) == chip8::opcode::LOAD_VX_TO_SOUND_TIMER );
}

TEST_CASE( "Binary-coded decimal opcodes are decoded", "[bcd]" )
{
    REQUIRE( OpDecoder::decode( 0xF033 ) == chip8::opcode::LOAD_VX_BCD_TO_I );
    REQUIRE( OpDecoder::decode( 0xFF33 ) == chip8::opcode::LOAD_VX_BCD_TO_I );
}

} // namespace
