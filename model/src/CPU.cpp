#include <algorithm>

#include "CPU.hpp"

#include "WordDecoder.hpp"

namespace model
{

CPU::CPU( MMU& mmu, IoDevice& ioDevice, RandomNumberGenerator& rndGenerator )
: m_mmu{ mmu }
, m_ioDevice{ ioDevice }
, m_rndGenerator{ rndGenerator }
{
    m_registers.fill( 0x0 );
    m_mmu.load( chip8::font_set, 0x0 );
}

chip8::byte_t CPU::readRegister( const chip8::reg id ) const
{
    return m_registers.at( static_cast<std::size_t>( id ) );
}

void CPU::writeRegister( const chip8::reg id, const chip8::byte_t value )
{
    m_registers.at( static_cast<std::size_t>( id ) ) = value;
}

void CPU::loadToRegisters( const std::vector<chip8::byte_t> values )
{
    const auto size = std::min( values.size(), m_registers.size() );
    std::copy_n( std::begin( values ), size, std::begin( m_registers ) );
}

void CPU::cycle()
{
    if ( !isInterrupted )
    {
        fetch();
    }

    decode();
    execute();
    updateDelayTimer();
    updateSoundTimer();
}

void CPU::execute( const chip8::word_t instr )
{
    m_instruction = instr;
    decode();
    execute();
}

void CPU::fetch()
{
    m_instruction = m_mmu.readWord( m_pc );
    m_pc += chip8::instruction_size_in_bytes;
}

void CPU::decode()
{
    m_opcode = OpDecoder::decode( m_instruction );
}

void CPU::execute()
{
    switch ( m_opcode )
    {
        case chip8::opcode::clear_screen:
            clearDisplay();
            break;
        case chip8::opcode::ret:
            returnFromSubroutine();
            break;
        case chip8::opcode::jump:
            jumpToNnn();
            break;
        case chip8::opcode::call:
            callNNN();
            break;
        case chip8::opcode::skip_if_vx_equals_nn:
            skipIfVxEqualsNn();
            break;
        case chip8::opcode::skip_if_vx_not_equals_nn:
            skipIfVxNotEqualsNn();
            break;
        case chip8::opcode::skip_if_vx_equals_vy:
            skipIfVxEqualsVy();
            break;
        case chip8::opcode::load_nn_to_vx:
            loadNnToVx();
            break;
        case chip8::opcode::add_nn_to_vx:
            addNnToVx();
            break;
        case chip8::opcode::load_vy_to_vx:
            loadVyToVx();
            break;
        case chip8::opcode::vx_or_vy:
            bitwiseVxOrVy();
            break;
        case chip8::opcode::vx_and_vy:
            bitwiseVxAndVy();
            break;
        case chip8::opcode::vx_xor_vy:
            bitwiseVxXorVy();
            break;
        case chip8::opcode::vx_plus_vy:
            addVyToVx();
            break;
        case chip8::opcode::vx_minus_vy:
            subVyFromVx();
            break;
        case chip8::opcode::shift_vx_right:
            shiftVxRight();
            break;
        case chip8::opcode::set_vx_to_vy_minus_vx:
            subVxFromVy();
            break;
        case chip8::opcode::shift_vx_left:
            shiftVxLeft();
            break;
        case chip8::opcode::skip_if_vx_not_equals_vy:
            skipIfVxNotEqualsVy();
            break;
        case chip8::opcode::load_nnn_to_i:
            loadNnnToI();
            break;
        case chip8::opcode::jump_nnn_plus_v0:
            jumpToNnnPlusV0();
            break;
        case chip8::opcode::load_random_to_vx:
            executeLoadRandomToVx();
            break;
        case chip8::opcode::draw:
            draw();
            break;
        case chip8::opcode::skip_if_vx_is_pressed:
            executeSkipIfVxIsPressed();
            break;
        case chip8::opcode::skip_if_vx_is_not_pressed:
            executeSkipIfVxIsNotPressed();
            break;
        case chip8::opcode::load_delay_timer_to_vx:
            loadDelayToVx();
            break;
        case chip8::opcode::load_pressed_key_to_vx:
            executeWaitPressedKeyToVx();
            break;
        case chip8::opcode::load_vx_to_delay_timer:
            loadVxToDelay();
            break;
        case chip8::opcode::load_vx_to_sound_timer:
            loadVxToSound();
            break;
        case chip8::opcode::add_vx_to_i:
            addVxToI();
            break;
        case chip8::opcode::load_font_sprite_address_to_i:
            loadFontSpriteAddressToI();
            break;
        case chip8::opcode::load_vx_bcd_to_i:
            executeLoadVxBcdToI();
            break;
        case chip8::opcode::load_v0_to_vx_in_address_i:
            loadRegistersToI();
            break;
        case chip8::opcode::load_address_i_to_v0_to_vx:
            loadItoRegisters();
            break;
        default:
            // chip8::OpCode::INVALID
            break;
    }
}

void CPU::updateDelayTimer()
{
    if ( m_delayTimer > 0 )
    {
        --m_delayTimer;
    }
}

void CPU::updateSoundTimer()
{
    if ( m_soundTimer > 0 )
    {
        --m_soundTimer;
    }
}

void CPU::clearDisplay()
{
    m_frameBuffer.fill( 0x0 );
    m_ioDevice.drawScreen( m_frameBuffer );
}

void CPU::jumpToNnn()
{
    m_pc = WordDecoder::readNNN( m_instruction );
}

void CPU::returnFromSubroutine()
{
    m_pc = m_stack.at( --m_sp );
}

void CPU::callNNN()
{
    m_stack.at( m_sp++ ) = m_pc;
    m_pc                 = WordDecoder::readNNN( m_instruction );
}

void CPU::skipIfVxEqualsNn()
{
    const auto x  = WordDecoder::readX( m_instruction );
    const auto nn = WordDecoder::readNN( m_instruction );

    if ( m_registers.at( x ) == nn )
    {
        m_pc += chip8::instruction_size_in_bytes;
    }
}

void CPU::skipIfVxNotEqualsNn()
{
    const auto x  = WordDecoder::readX( m_instruction );
    const auto nn = WordDecoder::readNN( m_instruction );

    if ( m_registers.at( x ) != nn )
    {
        m_pc += chip8::instruction_size_in_bytes;
    }
}

void CPU::skipIfVxEqualsVy()
{
    const auto x = WordDecoder::readX( m_instruction );
    const auto y = WordDecoder::readY( m_instruction );

    if ( m_registers.at( x ) == m_registers.at( y ) )
    {
        m_pc += chip8::instruction_size_in_bytes;
    }
}

void CPU::skipIfVxNotEqualsVy()
{
    const auto x = WordDecoder::readX( m_instruction );
    const auto y = WordDecoder::readY( m_instruction );

    if ( m_registers.at( x ) != m_registers.at( y ) )
    {
        m_pc += chip8::instruction_size_in_bytes;
    }
}

void CPU::loadNnToVx()
{
    const auto x        = WordDecoder::readX( m_instruction );
    const auto nn       = WordDecoder::readNN( m_instruction );
    m_registers.at( x ) = nn;
}

void CPU::addNnToVx()
{
    const auto x  = WordDecoder::readX( m_instruction );
    const auto nn = WordDecoder::readNN( m_instruction );
    m_registers.at( x ) += nn;
}

void CPU::loadVyToVx()
{
    const auto x        = WordDecoder::readX( m_instruction );
    const auto y        = WordDecoder::readY( m_instruction );
    m_registers.at( x ) = m_registers.at( y );
}

void CPU::bitwiseVxOrVy()
{
    const auto x = WordDecoder::readX( m_instruction );
    const auto y = WordDecoder::readY( m_instruction );
    m_registers.at( x ) |= m_registers.at( y );
}

void CPU::bitwiseVxAndVy()
{
    const auto x = WordDecoder::readX( m_instruction );
    const auto y = WordDecoder::readY( m_instruction );
    m_registers.at( x ) &= m_registers.at( y );
}

void CPU::bitwiseVxXorVy()
{
    const auto x = WordDecoder::readX( m_instruction );
    const auto y = WordDecoder::readY( m_instruction );
    m_registers.at( x ) ^= m_registers.at( y );
}

void CPU::shiftVxRight()
{
    const auto x    = WordDecoder::readX( m_instruction );
    const auto mask = static_cast<chip8::byte_t>( 0x1 );
    auto&      vx   = m_registers.at( x );

    writeRegister( chip8::reg::vf, vx & mask );
    vx >>= 1;
}

void CPU::shiftVxLeft()
{
    const auto x  = WordDecoder::readX( m_instruction );
    auto&      vx = m_registers.at( x );

    writeRegister( chip8::reg::vf, vx >> 7 );
    vx <<= 1;
}

void CPU::addVyToVx()
{
    const auto x = WordDecoder::readX( m_instruction );
    const auto y = WordDecoder::readY( m_instruction );

    auto&       vx = m_registers.at( x );
    const auto& vy = m_registers.at( y );

    const auto hasCarry = vy > ( 0xFF - vx );
    writeRegister( chip8::reg::vf, hasCarry ? 0x1 : 0x0 );

    vx += vy;
}

void CPU::subVyFromVx()
{
    const auto x = WordDecoder::readX( m_instruction );
    const auto y = WordDecoder::readY( m_instruction );

    auto&       vx = m_registers.at( x );
    const auto& vy = m_registers.at( y );

    const auto hasBorrow = vy > vx;
    writeRegister( chip8::reg::vf, hasBorrow ? 0x0 : 0x1 );

    vx -= vy;
}

void CPU::subVxFromVy()
{
    const auto x = WordDecoder::readX( m_instruction );
    const auto y = WordDecoder::readY( m_instruction );

    auto&       vx = m_registers.at( x );
    const auto& vy = m_registers.at( y );

    const auto hasBorrow = vx > vy;
    writeRegister( chip8::reg::vf, hasBorrow ? 0x0 : 0x1 );

    vx = vy - vx;
}

void CPU::jumpToNnnPlusV0()
{
    m_pc = WordDecoder::readNNN( m_instruction ) + m_registers.at( 0x0 );
}

void CPU::loadDelayToVx()
{
    const auto x        = WordDecoder::readX( m_instruction );
    m_registers.at( x ) = m_delayTimer;
}

void CPU::loadVxToDelay()
{
    const auto x = WordDecoder::readX( m_instruction );
    m_delayTimer = m_registers.at( x );
}

void CPU::loadVxToSound()
{
    const auto x = WordDecoder::readX( m_instruction );
    m_soundTimer = m_registers.at( x );
}

void CPU::loadNnnToI()
{
    m_I = WordDecoder::readNNN( m_instruction );
}

void CPU::loadRegistersToI()
{
    const auto x    = WordDecoder::readX( m_instruction );
    const auto size = x + 1u;

    std::copy_n( std::begin( m_registers ), size, std::begin( m_mmu ) + m_I );
}

void CPU::loadItoRegisters()
{
    const auto x    = WordDecoder::readX( m_instruction );
    const auto size = x + 1u;

    std::copy_n( std::begin( m_mmu ) + m_I, size, std::begin( m_registers ) );
}

void CPU::addVxToI()
{
    const auto x = WordDecoder::readX( m_instruction );
    m_I += m_registers.at( x );
}

void CPU::loadFontSpriteAddressToI()
{
    const auto x = WordDecoder::readX( m_instruction );
    m_I          = m_registers.at( x ) * chip8::char_sprite_size;
}

void CPU::draw()
{
    const auto vx     = WordDecoder::readX( m_instruction );
    const auto vy     = WordDecoder::readY( m_instruction );
    const auto x      = m_registers.at( vx );
    const auto y      = m_registers.at( vy );
    const auto height = WordDecoder::readN( m_instruction );

    chip8::byte_t flipped{ 0x0u };

    for ( auto line = 0u; line < height; ++line )
    {
        const auto rowPixels = m_mmu.readByte( m_I + line );

        for ( auto row = 0u; row < chip8::sprite_width; ++row )
        {
            if ( ( rowPixels & ( 0x80 >> row ) ) != 0 )
            {
                const auto     offset = ( x + row + ( ( y + line ) * 64 ) ) % 2048;
                chip8::byte_t& pixel  = m_frameBuffer.at( offset );

                if ( pixel != 0 )
                {
                    flipped = 1u;
                }

                pixel ^= 1u;
            }
        }
    }

    writeRegister( chip8::reg::vf, flipped );
    m_ioDevice.drawScreen( m_frameBuffer );
}

void CPU::executeSkipIfVxIsPressed()
{
    const auto x   = WordDecoder::readX( m_instruction );
    const auto key = static_cast<chip8::key>( m_registers.at( x ) );

    if ( m_ioDevice.isKeyPressed( key ) )
    {
        m_pc += chip8::instruction_size_in_bytes;
    }
}

void CPU::executeSkipIfVxIsNotPressed()
{
    const auto x   = WordDecoder::readX( m_instruction );
    const auto key = static_cast<chip8::key>( m_registers.at( x ) );

    if ( !m_ioDevice.isKeyPressed( key ) )
    {
        m_pc += chip8::instruction_size_in_bytes;
    }
}

void CPU::executeWaitPressedKeyToVx()
{
    isInterrupted         = true;
    const auto pressedKey = m_ioDevice.getPressedKey();

    if ( pressedKey != chip8::key::none )
    {
        const auto x        = WordDecoder::readX( m_instruction );
        m_registers.at( x ) = static_cast<chip8::byte_t>( pressedKey );
        isInterrupted       = false;
    }
}

void CPU::executeLoadVxBcdToI()
{
    const auto x  = WordDecoder::readX( m_instruction );
    const auto vx = m_registers.at( x );

    const auto hundreds = vx / 100;
    const auto tens     = ( vx / 10 ) % 10;
    const auto ones     = ( vx % 100 ) % 10;

    m_mmu.writeByte( hundreds, m_I );
    m_mmu.writeByte( tens, m_I + 1u );
    m_mmu.writeByte( ones, m_I + 2u );
}

void CPU::executeLoadRandomToVx()
{
    const auto x            = WordDecoder::readX( m_instruction );
    const auto nn           = WordDecoder::readNN( m_instruction );
    const auto randomNumber = m_rndGenerator.get();

    m_registers.at( x ) = nn & randomNumber;
}

} // namespace model
