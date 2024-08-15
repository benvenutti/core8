#include <catch2/catch_test_macros.hpp>

#include "model/OpDecoder.hpp"

namespace
{

using namespace model;

TEST_CASE( "Display opcodes are decoded", "[display]" )
{
    REQUIRE( opdecoder::decode( 0x00E0 ) == chip8::opcode::clear_screen );

    REQUIRE( opdecoder::decode( 0xD000 ) == chip8::opcode::draw );
    REQUIRE( opdecoder::decode( 0xDFFF ) == chip8::opcode::draw );
}

TEST_CASE( "Flow opcodes are decoded", "[flow]" )
{
    REQUIRE( opdecoder::decode( 0x00EE ) == chip8::opcode::ret );

    REQUIRE( opdecoder::decode( 0x1000 ) == chip8::opcode::jump );
    REQUIRE( opdecoder::decode( 0x1FFF ) == chip8::opcode::jump );

    REQUIRE( opdecoder::decode( 0x2000 ) == chip8::opcode::call );
    REQUIRE( opdecoder::decode( 0x2FFF ) == chip8::opcode::call );

    REQUIRE( opdecoder::decode( 0xB000 ) == chip8::opcode::jump_nnn_plus_v0 );
    REQUIRE( opdecoder::decode( 0xBFFF ) == chip8::opcode::jump_nnn_plus_v0 );
}

TEST_CASE( "Conditional opcodes are decoded", "[conditional]" )
{
    REQUIRE( opdecoder::decode( 0x3000 ) == chip8::opcode::skip_if_vx_equals_nn );
    REQUIRE( opdecoder::decode( 0x3FFF ) == chip8::opcode::skip_if_vx_equals_nn );

    REQUIRE( opdecoder::decode( 0x4000 ) == chip8::opcode::skip_if_vx_not_equals_nn );
    REQUIRE( opdecoder::decode( 0x4FFF ) == chip8::opcode::skip_if_vx_not_equals_nn );

    REQUIRE( opdecoder::decode( 0x5000 ) == chip8::opcode::skip_if_vx_equals_vy );
    REQUIRE( opdecoder::decode( 0x5FF0 ) == chip8::opcode::skip_if_vx_equals_vy );

    REQUIRE( opdecoder::decode( 0x9000 ) == chip8::opcode::skip_if_vx_not_equals_vy );
    REQUIRE( opdecoder::decode( 0x9FF0 ) == chip8::opcode::skip_if_vx_not_equals_vy );
}

TEST_CASE( "Constant opcodes are decoded", "[constant]" )
{
    REQUIRE( opdecoder::decode( 0x6000 ) == chip8::opcode::load_nn_to_vx );
    REQUIRE( opdecoder::decode( 0x6FFF ) == chip8::opcode::load_nn_to_vx );

    REQUIRE( opdecoder::decode( 0x7000 ) == chip8::opcode::add_nn_to_vx );
    REQUIRE( opdecoder::decode( 0x7FFF ) == chip8::opcode::add_nn_to_vx );
}

TEST_CASE( "Assignment opcodes are decoded", "[assign]" )
{
    REQUIRE( opdecoder::decode( 0x8000 ) == chip8::opcode::load_vy_to_vx );
    REQUIRE( opdecoder::decode( 0x8FF0 ) == chip8::opcode::load_vy_to_vx );
    REQUIRE( opdecoder::decode( 0x8FFF ) != chip8::opcode::load_vy_to_vx );
}

TEST_CASE( "Bitwise operation opcodes are decoded", "[bitwise]" )
{
    REQUIRE( opdecoder::decode( 0x8001 ) == chip8::opcode::vx_or_vy );
    REQUIRE( opdecoder::decode( 0x8FF1 ) == chip8::opcode::vx_or_vy );

    REQUIRE( opdecoder::decode( 0x8002 ) == chip8::opcode::vx_and_vy );
    REQUIRE( opdecoder::decode( 0x8FF2 ) == chip8::opcode::vx_and_vy );

    REQUIRE( opdecoder::decode( 0x8003 ) == chip8::opcode::vx_xor_vy );
    REQUIRE( opdecoder::decode( 0x8FF3 ) == chip8::opcode::vx_xor_vy );

    REQUIRE( opdecoder::decode( 0x8006 ) == chip8::opcode::shift_vx_right );
    REQUIRE( opdecoder::decode( 0x8FF6 ) == chip8::opcode::shift_vx_right );

    REQUIRE( opdecoder::decode( 0x800E ) == chip8::opcode::shift_vx_left );
    REQUIRE( opdecoder::decode( 0x8FFE ) == chip8::opcode::shift_vx_left );
}

TEST_CASE( "Mathematical opcodes are decoded", "[math]" )
{
    REQUIRE( opdecoder::decode( 0x8004 ) == chip8::opcode::vx_plus_vy );
    REQUIRE( opdecoder::decode( 0x8FF4 ) == chip8::opcode::vx_plus_vy );

    REQUIRE( opdecoder::decode( 0x8005 ) == chip8::opcode::vx_minus_vy );
    REQUIRE( opdecoder::decode( 0x8FF5 ) == chip8::opcode::vx_minus_vy );

    REQUIRE( opdecoder::decode( 0x8007 ) == chip8::opcode::set_vx_to_vy_minus_vx );
    REQUIRE( opdecoder::decode( 0x8FF7 ) == chip8::opcode::set_vx_to_vy_minus_vx );
}

TEST_CASE( "Memory access opcodes are decoded", "[memory]" )
{
    REQUIRE( opdecoder::decode( 0xA000 ) == chip8::opcode::load_nnn_to_i );
    REQUIRE( opdecoder::decode( 0xAFFF ) == chip8::opcode::load_nnn_to_i );

    REQUIRE( opdecoder::decode( 0xF01E ) == chip8::opcode::add_vx_to_i );
    REQUIRE( opdecoder::decode( 0xFF1E ) == chip8::opcode::add_vx_to_i );

    REQUIRE( opdecoder::decode( 0xF029 ) == chip8::opcode::load_font_sprite_address_to_i );
    REQUIRE( opdecoder::decode( 0xFF29 ) == chip8::opcode::load_font_sprite_address_to_i );

    REQUIRE( opdecoder::decode( 0xF055 ) == chip8::opcode::load_v0_to_vx_in_address_i );
    REQUIRE( opdecoder::decode( 0xFF55 ) == chip8::opcode::load_v0_to_vx_in_address_i );

    REQUIRE( opdecoder::decode( 0xF065 ) == chip8::opcode::load_address_i_to_v0_to_vx );
    REQUIRE( opdecoder::decode( 0xFF65 ) == chip8::opcode::load_address_i_to_v0_to_vx );
}

TEST_CASE( "Random number generation opcodes are decoded", "[random]" )
{
    REQUIRE( opdecoder::decode( 0xC000 ) == chip8::opcode::load_random_to_vx );
    REQUIRE( opdecoder::decode( 0xCFFF ) == chip8::opcode::load_random_to_vx );
}

TEST_CASE( "Keypad opcodes are decoded", "[keypad]" )
{
    REQUIRE( opdecoder::decode( 0xE09E ) == chip8::opcode::skip_if_vx_is_pressed );
    REQUIRE( opdecoder::decode( 0xEF9E ) == chip8::opcode::skip_if_vx_is_pressed );

    REQUIRE( opdecoder::decode( 0xE0A1 ) == chip8::opcode::skip_if_vx_is_not_pressed );
    REQUIRE( opdecoder::decode( 0xEFA1 ) == chip8::opcode::skip_if_vx_is_not_pressed );

    REQUIRE( opdecoder::decode( 0xF00A ) == chip8::opcode::load_pressed_key_to_vx );
    REQUIRE( opdecoder::decode( 0xFF0A ) == chip8::opcode::load_pressed_key_to_vx );
}

TEST_CASE( "Timer opcodes are decoded", "[timer]" )
{
    REQUIRE( opdecoder::decode( 0xF007 ) == chip8::opcode::load_delay_timer_to_vx );
    REQUIRE( opdecoder::decode( 0xFF07 ) == chip8::opcode::load_delay_timer_to_vx );

    REQUIRE( opdecoder::decode( 0xF015 ) == chip8::opcode::load_vx_to_delay_timer );
    REQUIRE( opdecoder::decode( 0xFF15 ) == chip8::opcode::load_vx_to_delay_timer );
}

TEST_CASE( "Sound opcodes are decoded", "[sound]" )
{
    REQUIRE( opdecoder::decode( 0xF018 ) == chip8::opcode::load_vx_to_sound_timer );
    REQUIRE( opdecoder::decode( 0xFF18 ) == chip8::opcode::load_vx_to_sound_timer );
}

TEST_CASE( "Binary-coded decimal opcodes are decoded", "[bcd]" )
{
    REQUIRE( opdecoder::decode( 0xF033 ) == chip8::opcode::load_vx_bcd_to_i );
    REQUIRE( opdecoder::decode( 0xFF33 ) == chip8::opcode::load_vx_bcd_to_i );
}

} // namespace
