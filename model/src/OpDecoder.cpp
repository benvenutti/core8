#include "OpDecoder.hpp"

namespace Core8
{

Chip8::OpCode OpDecoder::decode( const Chip8::WORD word )
{
    switch ( word & 0xF000 )
    {
        case 0x0000:
            switch ( word & 0X00EF )
            {
                case 0x00E0:
                    return Chip8::OpCode::CLEAR_SCREEN;
                case 0x00EE:
                    return Chip8::OpCode::RETURN;
                default:
                    return Chip8::OpCode::INVALID;
            }
        case 0x1000:
            return Chip8::OpCode::JUMP;
        case 0x2000:
            return Chip8::OpCode::CALL;
        case 0x3000:
            return Chip8::OpCode::SKIP_IF_VX_EQUALS_NN;
        case 0x4000:
            return Chip8::OpCode::SKIP_IF_VX_NOT_EQUALS_NN;
        case 0x5000:
            return Chip8::OpCode::SKIP_IF_VX_EQUALS_VY;
        case 0x6000:
            return Chip8::OpCode::LOAD_NN_TO_VX;
        case 0x7000:
            return Chip8::OpCode::ADD_NN_TO_VX;
        case 0x8000:
            switch ( word & 0x000F )
            {
                case 0x0000:
                    return Chip8::OpCode::LOAD_VY_TO_VX;
                case 0x0001:
                    return Chip8::OpCode::VX_OR_VY;
                case 0x0002:
                    return Chip8::OpCode::VX_AND_VY;
                case 0x0003:
                    return Chip8::OpCode::VX_XOR_VY;
                case 0x0004:
                    return Chip8::OpCode::VX_PLUS_VY;
                case 0x0005:
                    return Chip8::OpCode::VX_MINUS_VY;
                case 0x0006:
                    return Chip8::OpCode::SHIFT_VX_RIGHT;
                case 0x0007:
                    return Chip8::OpCode::SET_VX_TO_VY_MINUS_VX;
                case 0x000E:
                    return Chip8::OpCode::SHIFT_VX_LEFT;
                default:
                    return Chip8::OpCode::INVALID;
            }
        case 0x9000:
            return Chip8::OpCode::SKIP_IF_VX_NOT_EQUALS_VY;
        case 0xA000:
            return Chip8::OpCode::LOAD_NNN_TO_I;
        case 0xB000:
            return Chip8::OpCode::JUMP_NNN_PLUS_V0;
        case 0xC000:
            return Chip8::OpCode::LOAD_RANDOM_TO_VX;
        case 0xD000:
            return Chip8::OpCode::DRAW;
        case 0xE000:
            switch ( word & 0x00FF )
            {
                case 0x009E:
                    return Chip8::OpCode::SKIP_IF_VX_IS_PRESSED;
                case 0x00A1:
                    return Chip8::OpCode::SKIP_IF_VX_IS_NOT_PRESSED;
                default:
                    return Chip8::OpCode::INVALID;
            }
        case 0xF000:
            switch ( word & 0x00FF )
            {
                case 0x0007:
                    return Chip8::OpCode::LOAD_DELAY_TIMER_TO_VX;
                case 0x000A:
                    return Chip8::OpCode::LOAD_PRESSED_KEY_TO_VX;
                case 0x0015:
                    return Chip8::OpCode::LOAD_VX_TO_DELAY_TIMER;
                case 0x0018:
                    return Chip8::OpCode::LOAD_VX_TO_SOUND_TIMER;
                case 0x001E:
                    return Chip8::OpCode::ADD_VX_TO_I;
                case 0x0029:
                    return Chip8::OpCode::LOAD_FONT_SPRITE_ADDRESS_TO_I;
                case 0x0033:
                    return Chip8::OpCode::LOAD_VX_BCD_TO_I;
                case 0x0055:
                    return Chip8::OpCode::LOAD_V0_TO_VX_IN_ADDRESS_I;
                case 0x0065:
                    return Chip8::OpCode::LOAD_ADDRESS_I_TO_V0_TO_VX;
                default:
                    return Chip8::OpCode::INVALID;
            }
        default:
            return Chip8::OpCode::INVALID;
    }
}

} // namespace Core8
