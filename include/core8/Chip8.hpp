#ifndef CORE8_CHIP8_H
#define CORE8_CHIP8_H

#include <cstdint>

namespace Core8 {
namespace Chip8 {

using BYTE = uint8_t;
using WORD = uint16_t;

const std::size_t RAM_SIZE{4096};

enum class OPCODE {
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
    LOAD_SPRITE_TO_I,
    LOAD_VX_BCD_TO_I,
    LOAD_V0_TO_VX_IN_ADDRESS_I,
    LOAD_ADDRESS_I_TO_V0_TO_VX,
    INVALID
};

} // namespace Chip8
} // namespace Core8

#endif