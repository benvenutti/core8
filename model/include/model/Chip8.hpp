#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace model
{
namespace chip8
{

using byte_t = std::uint8_t;
using word_t = std::uint16_t;

constexpr word_t ram_size{ 4096 };
constexpr word_t num_registers{ 16 };
constexpr word_t init_rom_load_address{ 512 };
constexpr word_t instruction_size_in_bytes{ 2 };
constexpr word_t stack_size{ 16 };
constexpr word_t display_width{ 64 };
constexpr word_t display_height{ 32 };
constexpr word_t display_size{ display_width * display_height };

constexpr byte_t char_sprite_size{ 5 };
constexpr byte_t sprite_width{ 8 };

enum class registers
{
    v0,
    v1,
    v2,
    v3,
    v4,
    v5,
    v6,
    v7,
    v8,
    v9,
    va,
    vb,
    vc,
    vd,
    ve,
    vf
};

enum class opcode
{
    CLEAR_SCREEN,
    RETURN,
    JUMP,
    CALL,
    SKIP_IF_VX_EQUALS_NN,
    SKIP_IF_VX_NOT_EQUALS_NN,
    SKIP_IF_VX_EQUALS_VY,
    LOAD_NN_TO_VX,
    ADD_NN_TO_VX,
    LOAD_VY_TO_VX,
    VX_OR_VY,
    VX_AND_VY,
    VX_XOR_VY,
    VX_PLUS_VY,
    VX_MINUS_VY,
    SHIFT_VX_RIGHT,
    SET_VX_TO_VY_MINUS_VX,
    SHIFT_VX_LEFT,
    SKIP_IF_VX_NOT_EQUALS_VY,
    LOAD_NNN_TO_I,
    JUMP_NNN_PLUS_V0,
    LOAD_RANDOM_TO_VX,
    DRAW,
    SKIP_IF_VX_IS_PRESSED,
    SKIP_IF_VX_IS_NOT_PRESSED,
    LOAD_DELAY_TIMER_TO_VX,
    LOAD_PRESSED_KEY_TO_VX,
    LOAD_VX_TO_DELAY_TIMER,
    LOAD_VX_TO_SOUND_TIMER,
    ADD_VX_TO_I,
    LOAD_FONT_SPRITE_ADDRESS_TO_I,
    LOAD_VX_BCD_TO_I,
    LOAD_V0_TO_VX_IN_ADDRESS_I,
    LOAD_ADDRESS_I_TO_V0_TO_VX,
    INVALID
};

enum class key
{
    K0,
    K1,
    K2,
    K3,
    K4,
    K5,
    K6,
    K7,
    K8,
    K9,
    KA,
    KB,
    KC,
    KD,
    KE,
    KF,
    NONE
};

const std::vector<byte_t> font_set{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

} // namespace chip8
} // namespace model
