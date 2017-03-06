#ifndef CORE8_CHIP8_H
#define CORE8_CHIP8_H

#include <cstddef>
#include <cstdint>
#include <vector>

namespace Core8 {
namespace Chip8 {

using BYTE = std::uint8_t;
using WORD = std::uint16_t;

const std::size_t RAM_SIZE{4096};
const std::size_t NUMBER_OF_REGISTERS{16};
const std::size_t INIT_ROM_LOAD_ADDRESS{512};
const std::size_t INSTRUCTION_BYTE_SIZE{2};
const std::size_t STACK_SIZE{16};
const std::size_t DISPLAY_WIDTH{64};
const std::size_t DISPLAY_HEIGHT{32};
const std::size_t DISPLAY_SIZE{DISPLAY_WIDTH * DISPLAY_HEIGHT};

enum class REGISTER {
    V0, V1, V2, V3, V4, V5, V6, V7,
    V8, V9, VA, VB, VC, VD, VE, VF
};

enum class OpCode {
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

const BYTE CHAR_SPRITE_SIZE{5};
const BYTE SPRITE_WIDTH{8};

enum class KEY {
    K0, K1, K2, K3, K4, K5, K6, K7,
    K8, K9, KA, KB, KC, KD, KE, KF, NONE
};

const std::vector<BYTE> FONT_SET{
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

} // namespace Chip8
} // namespace Core8

#endif