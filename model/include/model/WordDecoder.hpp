#pragma once

#include <model/Chip8.hpp>

namespace model::WordDecoder
{

/// Reads byte value of X on pattern vXvv.
inline chip8::byte_t readX( const chip8::word_t instr )
{
    return static_cast<chip8::byte_t>( ( instr & 0x0F00 ) >> 8 );
}

/// Reads byte value of Y on pattern vvYv.
inline chip8::byte_t readY( const chip8::word_t instr )
{
    return static_cast<chip8::byte_t>( ( instr & 0x00F0 ) >> 4 );
}

/// Reads byte value of N on pattern vvvN.
inline chip8::byte_t readN( const chip8::word_t instr )
{
    return static_cast<chip8::byte_t>( instr & 0x000F );
}

/// Reads byte value of NN on pattern vvNN.
inline chip8::byte_t readNN( const chip8::word_t instr )
{
    return static_cast<chip8::byte_t>( instr & 0x00FF );
}

/// Reads word value of NNN on pattern vNNN.
inline chip8::word_t readNNN( const chip8::word_t instr )
{
    return instr & 0x0FFF;
}

} // namespace model::WordDecoder
