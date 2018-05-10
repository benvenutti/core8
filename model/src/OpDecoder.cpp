#include "OpDecoder.hpp"

namespace model
{

chip8::opcode OpDecoder::decode( const chip8::word_t word )
{
    switch ( word & 0xF000 )
    {
        case 0x0000:
            switch ( word & 0X00EF )
            {
                case 0x00E0:
                    return chip8::opcode::CLEAR_SCREEN;
                case 0x00EE:
                    return chip8::opcode::RETURN;
                default:
                    return chip8::opcode::INVALID;
            }
        case 0x1000:
            return chip8::opcode::JUMP;
        case 0x2000:
            return chip8::opcode::CALL;
        case 0x3000:
            return chip8::opcode::SKIP_IF_VX_EQUALS_NN;
        case 0x4000:
            return chip8::opcode::SKIP_IF_VX_NOT_EQUALS_NN;
        case 0x5000:
            return chip8::opcode::SKIP_IF_VX_EQUALS_VY;
        case 0x6000:
            return chip8::opcode::LOAD_NN_TO_VX;
        case 0x7000:
            return chip8::opcode::ADD_NN_TO_VX;
        case 0x8000:
            switch ( word & 0x000F )
            {
                case 0x0000:
                    return chip8::opcode::LOAD_VY_TO_VX;
                case 0x0001:
                    return chip8::opcode::VX_OR_VY;
                case 0x0002:
                    return chip8::opcode::VX_AND_VY;
                case 0x0003:
                    return chip8::opcode::VX_XOR_VY;
                case 0x0004:
                    return chip8::opcode::VX_PLUS_VY;
                case 0x0005:
                    return chip8::opcode::VX_MINUS_VY;
                case 0x0006:
                    return chip8::opcode::SHIFT_VX_RIGHT;
                case 0x0007:
                    return chip8::opcode::SET_VX_TO_VY_MINUS_VX;
                case 0x000E:
                    return chip8::opcode::SHIFT_VX_LEFT;
                default:
                    return chip8::opcode::INVALID;
            }
        case 0x9000:
            return chip8::opcode::SKIP_IF_VX_NOT_EQUALS_VY;
        case 0xA000:
            return chip8::opcode::LOAD_NNN_TO_I;
        case 0xB000:
            return chip8::opcode::JUMP_NNN_PLUS_V0;
        case 0xC000:
            return chip8::opcode::LOAD_RANDOM_TO_VX;
        case 0xD000:
            return chip8::opcode::DRAW;
        case 0xE000:
            switch ( word & 0x00FF )
            {
                case 0x009E:
                    return chip8::opcode::SKIP_IF_VX_IS_PRESSED;
                case 0x00A1:
                    return chip8::opcode::SKIP_IF_VX_IS_NOT_PRESSED;
                default:
                    return chip8::opcode::INVALID;
            }
        case 0xF000:
            switch ( word & 0x00FF )
            {
                case 0x0007:
                    return chip8::opcode::LOAD_DELAY_TIMER_TO_VX;
                case 0x000A:
                    return chip8::opcode::LOAD_PRESSED_KEY_TO_VX;
                case 0x0015:
                    return chip8::opcode::LOAD_VX_TO_DELAY_TIMER;
                case 0x0018:
                    return chip8::opcode::LOAD_VX_TO_SOUND_TIMER;
                case 0x001E:
                    return chip8::opcode::ADD_VX_TO_I;
                case 0x0029:
                    return chip8::opcode::LOAD_FONT_SPRITE_ADDRESS_TO_I;
                case 0x0033:
                    return chip8::opcode::LOAD_VX_BCD_TO_I;
                case 0x0055:
                    return chip8::opcode::LOAD_V0_TO_VX_IN_ADDRESS_I;
                case 0x0065:
                    return chip8::opcode::LOAD_ADDRESS_I_TO_V0_TO_VX;
                default:
                    return chip8::opcode::INVALID;
            }
        default:
            return chip8::opcode::INVALID;
    }
}

} // namespace model
