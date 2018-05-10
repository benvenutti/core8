#include <algorithm>

#include "CPU.hpp"

#include "WordDecoder.hpp"

namespace Core8
{

CPU::CPU( MMU& mmu, IoDevice& ioDevice, RandomNumberGenerator& rndGenerator )
: m_mmu{ mmu }
, m_ioDevice{ ioDevice }
, m_rndGenerator{ rndGenerator }
{
    m_registers.fill( 0x0 );
    m_mmu.load( Chip8::FONT_SET, 0x0 );
}

Chip8::BYTE CPU::readRegister( const Chip8::Register id ) const
{
    return m_registers.at( static_cast<std::size_t>( id ) );
}

void CPU::writeRegister( const Chip8::Register id, const Chip8::BYTE value )
{
    m_registers.at( static_cast<std::size_t>( id ) ) = value;
}

void CPU::loadToRegisters( const std::vector<Chip8::BYTE> values )
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

void CPU::execute( const Chip8::WORD instr )
{
    m_instruction = instr;
    decode();
    execute();
}

void CPU::fetch()
{
    m_instruction = m_mmu.readWord( m_pc );
    m_pc += Chip8::INSTRUCTION_BYTE_SIZE;
}

void CPU::decode()
{
    m_opcode = OpDecoder::decode( m_instruction );
}

void CPU::execute()
{
    switch ( m_opcode )
    {
        case Chip8::OpCode::CLEAR_SCREEN:
            clearDisplay();
            break;
        case Chip8::OpCode::RETURN:
            returnFromSubroutine();
            break;
        case Chip8::OpCode::JUMP:
            jumpToNnn();
            break;
        case Chip8::OpCode::CALL:
            callNNN();
            break;
        case Chip8::OpCode::SKIP_IF_VX_EQUALS_NN:
            skipIfVxEqualsNn();
            break;
        case Chip8::OpCode::SKIP_IF_VX_NOT_EQUALS_NN:
            skipIfVxNotEqualsNn();
            break;
        case Chip8::OpCode::SKIP_IF_VX_EQUALS_VY:
            skipIfVxEqualsVy();
            break;
        case Chip8::OpCode::LOAD_NN_TO_VX:
            loadNnToVx();
            break;
        case Chip8::OpCode::ADD_NN_TO_VX:
            addNnToVx();
            break;
        case Chip8::OpCode::LOAD_VY_TO_VX:
            loadVyToVx();
            break;
        case Chip8::OpCode::VX_OR_VY:
            bitwiseVxOrVy();
            break;
        case Chip8::OpCode::VX_AND_VY:
            bitwiseVxAndVy();
            break;
        case Chip8::OpCode::VX_XOR_VY:
            bitwiseVxXorVy();
            break;
        case Chip8::OpCode::VX_PLUS_VY:
            addVyToVx();
            break;
        case Chip8::OpCode::VX_MINUS_VY:
            subVyFromVx();
            break;
        case Chip8::OpCode::SHIFT_VX_RIGHT:
            shiftVxRight();
            break;
        case Chip8::OpCode::SET_VX_TO_VY_MINUS_VX:
            subVxFromVy();
            break;
        case Chip8::OpCode::SHIFT_VX_LEFT:
            shiftVxLeft();
            break;
        case Chip8::OpCode::SKIP_IF_VX_NOT_EQUALS_VY:
            skipIfVxNotEqualsVy();
            break;
        case Chip8::OpCode::LOAD_NNN_TO_I:
            loadNnnToI();
            break;
        case Chip8::OpCode::JUMP_NNN_PLUS_V0:
            jumpToNnnPlusV0();
            break;
        case Chip8::OpCode::LOAD_RANDOM_TO_VX:
            executeLoadRandomToVx();
            break;
        case Chip8::OpCode::DRAW:
            draw();
            break;
        case Chip8::OpCode::SKIP_IF_VX_IS_PRESSED:
            executeSkipIfVxIsPressed();
            break;
        case Chip8::OpCode::SKIP_IF_VX_IS_NOT_PRESSED:
            executeSkipIfVxIsNotPressed();
            break;
        case Chip8::OpCode::LOAD_DELAY_TIMER_TO_VX:
            loadDelayToVx();
            break;
        case Chip8::OpCode::LOAD_PRESSED_KEY_TO_VX:
            executeWaitPressedKeyToVx();
            break;
        case Chip8::OpCode::LOAD_VX_TO_DELAY_TIMER:
            loadVxToDelay();
            break;
        case Chip8::OpCode::LOAD_VX_TO_SOUND_TIMER:
            loadVxToSound();
            break;
        case Chip8::OpCode::ADD_VX_TO_I:
            addVxToI();
            break;
        case Chip8::OpCode::LOAD_FONT_SPRITE_ADDRESS_TO_I:
            loadFontSpriteAddressToI();
            break;
        case Chip8::OpCode::LOAD_VX_BCD_TO_I:
            executeLoadVxBcdToI();
            break;
        case Chip8::OpCode::LOAD_V0_TO_VX_IN_ADDRESS_I:
            loadRegistersToI();
            break;
        case Chip8::OpCode::LOAD_ADDRESS_I_TO_V0_TO_VX:
            loadItoRegisters();
            break;
        default:
            // Chip8::OpCode::INVALID
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
        m_pc += Chip8::INSTRUCTION_BYTE_SIZE;
    }
}

void CPU::skipIfVxNotEqualsNn()
{
    const auto x  = WordDecoder::readX( m_instruction );
    const auto nn = WordDecoder::readNN( m_instruction );

    if ( m_registers.at( x ) != nn )
    {
        m_pc += Chip8::INSTRUCTION_BYTE_SIZE;
    }
}

void CPU::skipIfVxEqualsVy()
{
    const auto x = WordDecoder::readX( m_instruction );
    const auto y = WordDecoder::readY( m_instruction );

    if ( m_registers.at( x ) == m_registers.at( y ) )
    {
        m_pc += Chip8::INSTRUCTION_BYTE_SIZE;
    }
}

void CPU::skipIfVxNotEqualsVy()
{
    const auto x = WordDecoder::readX( m_instruction );
    const auto y = WordDecoder::readY( m_instruction );

    if ( m_registers.at( x ) != m_registers.at( y ) )
    {
        m_pc += Chip8::INSTRUCTION_BYTE_SIZE;
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
    const auto mask = static_cast<Chip8::BYTE>( 0x1 );
    auto&      vx   = m_registers.at( x );

    writeRegister( Chip8::Register::VF, vx & mask );
    vx >>= 1;
}

void CPU::shiftVxLeft()
{
    const auto x  = WordDecoder::readX( m_instruction );
    auto&      vx = m_registers.at( x );

    writeRegister( Chip8::Register::VF, vx >> 7 );
    vx <<= 1;
}

void CPU::addVyToVx()
{
    const auto x = WordDecoder::readX( m_instruction );
    const auto y = WordDecoder::readY( m_instruction );

    auto&       vx = m_registers.at( x );
    const auto& vy = m_registers.at( y );

    const auto hasCarry = vy > ( 0xFF - vx );
    writeRegister( Chip8::Register::VF, hasCarry ? 0x1 : 0x0 );

    vx += vy;
}

void CPU::subVyFromVx()
{
    const auto x = WordDecoder::readX( m_instruction );
    const auto y = WordDecoder::readY( m_instruction );

    auto&       vx = m_registers.at( x );
    const auto& vy = m_registers.at( y );

    const auto hasBorrow = vy > vx;
    writeRegister( Chip8::Register::VF, hasBorrow ? 0x0 : 0x1 );

    vx -= vy;
}

void CPU::subVxFromVy()
{
    const auto x = WordDecoder::readX( m_instruction );
    const auto y = WordDecoder::readY( m_instruction );

    auto&       vx = m_registers.at( x );
    const auto& vy = m_registers.at( y );

    const auto hasBorrow = vx > vy;
    writeRegister( Chip8::Register::VF, hasBorrow ? 0x0 : 0x1 );

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
    m_I          = m_registers.at( x ) * Chip8::CHAR_SPRITE_SIZE;
}

void CPU::draw()
{
    const auto vx     = WordDecoder::readX( m_instruction );
    const auto vy     = WordDecoder::readY( m_instruction );
    const auto x      = m_registers.at( vx );
    const auto y      = m_registers.at( vy );
    const auto height = WordDecoder::readN( m_instruction );

    Chip8::BYTE flipped{ 0x0u };

    for ( auto line = 0u; line < height; ++line )
    {
        const auto rowPixels = m_mmu.readByte( m_I + line );

        for ( auto row = 0u; row < Chip8::SPRITE_WIDTH; ++row )
        {
            if ( ( rowPixels & ( 0x80 >> row ) ) != 0 )
            {
                const auto   offset = ( x + row + ( ( y + line ) * 64 ) ) % 2048;
                Chip8::BYTE& pixel  = m_frameBuffer.at( offset );

                if ( pixel != 0 )
                {
                    flipped = 1u;
                }

                pixel ^= 1u;
            }
        }
    }

    writeRegister( Chip8::Register::VF, flipped );
    m_ioDevice.drawScreen( m_frameBuffer );
}

void CPU::executeSkipIfVxIsPressed()
{
    const auto x   = WordDecoder::readX( m_instruction );
    const auto key = static_cast<Chip8::Key>( m_registers.at( x ) );

    if ( m_ioDevice.isKeyPressed( key ) )
    {
        m_pc += Chip8::INSTRUCTION_BYTE_SIZE;
    }
}

void CPU::executeSkipIfVxIsNotPressed()
{
    const auto x   = WordDecoder::readX( m_instruction );
    const auto key = static_cast<Chip8::Key>( m_registers.at( x ) );

    if ( !m_ioDevice.isKeyPressed( key ) )
    {
        m_pc += Chip8::INSTRUCTION_BYTE_SIZE;
    }
}

void CPU::executeWaitPressedKeyToVx()
{
    isInterrupted         = true;
    const auto pressedKey = m_ioDevice.getPressedKey();

    if ( pressedKey != Chip8::Key::NONE )
    {
        const auto x        = WordDecoder::readX( m_instruction );
        m_registers.at( x ) = static_cast<Chip8::BYTE>( pressedKey );
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

} // namespace Core8
