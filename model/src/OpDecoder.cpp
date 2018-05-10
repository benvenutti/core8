#include "OpDecoder.hpp"

namespace model
{

chip8::opcode opdecoder::decode( chip8::word_t word )
{
    switch ( word & 0xF000 )
    {
        case 0x0000:
            switch ( word & 0X00EF )
            {
                case 0x00E0:
                    return chip8::opcode::clear_screen;
                case 0x00EE:
                    return chip8::opcode::ret;
                default:
                    return chip8::opcode::invalid;
            }
        case 0x1000:
            return chip8::opcode::jump;
        case 0x2000:
            return chip8::opcode::call;
        case 0x3000:
            return chip8::opcode::skip_if_vx_equals_nn;
        case 0x4000:
            return chip8::opcode::skip_if_vx_not_equals_nn;
        case 0x5000:
            return chip8::opcode::skip_if_vx_equals_vy;
        case 0x6000:
            return chip8::opcode::load_nn_to_vx;
        case 0x7000:
            return chip8::opcode::add_nn_to_vx;
        case 0x8000:
            switch ( word & 0x000F )
            {
                case 0x0000:
                    return chip8::opcode::load_vy_to_vx;
                case 0x0001:
                    return chip8::opcode::vx_or_vy;
                case 0x0002:
                    return chip8::opcode::vx_and_vy;
                case 0x0003:
                    return chip8::opcode::vx_xor_vy;
                case 0x0004:
                    return chip8::opcode::vx_plus_vy;
                case 0x0005:
                    return chip8::opcode::vx_minus_vy;
                case 0x0006:
                    return chip8::opcode::shift_vx_right;
                case 0x0007:
                    return chip8::opcode::set_vx_to_vy_minus_vx;
                case 0x000E:
                    return chip8::opcode::shift_vx_left;
                default:
                    return chip8::opcode::invalid;
            }
        case 0x9000:
            return chip8::opcode::skip_if_vx_not_equals_vy;
        case 0xA000:
            return chip8::opcode::load_nnn_to_i;
        case 0xB000:
            return chip8::opcode::jump_nnn_plus_v0;
        case 0xC000:
            return chip8::opcode::load_random_to_vx;
        case 0xD000:
            return chip8::opcode::draw;
        case 0xE000:
            switch ( word & 0x00FF )
            {
                case 0x009E:
                    return chip8::opcode::skip_if_vx_is_pressed;
                case 0x00A1:
                    return chip8::opcode::skip_if_vx_is_not_pressed;
                default:
                    return chip8::opcode::invalid;
            }
        case 0xF000:
            switch ( word & 0x00FF )
            {
                case 0x0007:
                    return chip8::opcode::load_delay_timer_to_vx;
                case 0x000A:
                    return chip8::opcode::load_pressed_key_to_vx;
                case 0x0015:
                    return chip8::opcode::load_vx_to_delay_timer;
                case 0x0018:
                    return chip8::opcode::load_vx_to_sound_timer;
                case 0x001E:
                    return chip8::opcode::add_vx_to_i;
                case 0x0029:
                    return chip8::opcode::load_font_sprite_address_to_i;
                case 0x0033:
                    return chip8::opcode::load_vx_bcd_to_i;
                case 0x0055:
                    return chip8::opcode::load_v0_to_vx_in_address_i;
                case 0x0065:
                    return chip8::opcode::load_address_i_to_v0_to_vx;
                default:
                    return chip8::opcode::invalid;
            }
        default:
            return chip8::opcode::invalid;
    }
}

} // namespace model
