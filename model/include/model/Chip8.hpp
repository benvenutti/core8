#pragma once

#include <cstdint>
#include <vector>

namespace model::chip8
{

using byte_t = std::uint8_t;
using word_t = std::uint16_t;

constexpr word_t ram_size{ 4096 };
constexpr word_t num_registers{ 16 };
constexpr word_t init_rom_load_address{ 512 };
constexpr word_t instruction_size_in_bytes{ 2 };
constexpr word_t stack_size{ 16 };
constexpr word_t keypad_size{ 16 };
constexpr word_t display_width{ 64 };
constexpr word_t display_height{ 32 };
constexpr word_t display_size{ display_width * display_height };

constexpr byte_t char_sprite_size{ 5 };
constexpr byte_t sprite_width{ 8 };

enum class reg // register
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
    clear_screen,
    ret,
    jump,
    call,
    skip_if_vx_equals_nn,
    skip_if_vx_not_equals_nn,
    skip_if_vx_equals_vy,
    load_nn_to_vx,
    add_nn_to_vx,
    load_vy_to_vx,
    vx_or_vy,
    vx_and_vy,
    vx_xor_vy,
    vx_plus_vy,
    vx_minus_vy,
    shift_vx_right,
    set_vx_to_vy_minus_vx,
    shift_vx_left,
    skip_if_vx_not_equals_vy,
    load_nnn_to_i,
    jump_nnn_plus_v0,
    load_random_to_vx,
    draw,
    skip_if_vx_is_pressed,
    skip_if_vx_is_not_pressed,
    load_delay_timer_to_vx,
    load_pressed_key_to_vx,
    load_vx_to_delay_timer,
    load_vx_to_sound_timer,
    add_vx_to_i,
    load_font_sprite_address_to_i,
    load_vx_bcd_to_i,
    load_v0_to_vx_in_address_i,
    load_address_i_to_v0_to_vx,
    invalid
};

enum class key
{
    k0,
    k1,
    k2,
    k3,
    k4,
    k5,
    k6,
    k7,
    k8,
    k9,
    ka,
    kb,
    kc,
    kd,
    ke,
    kf
};

const std::vector< byte_t > font_set{
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

} // namespace model::chip8
