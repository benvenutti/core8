#pragma once

#include "Chip8.hpp"

namespace model
{
namespace WordDecoder
{

/// Reads byte value of X on pattern vXvv.
inline Chip8::byte_t readX( const Chip8::word_t instr )
{
    return static_cast<Chip8::byte_t>( ( instr & 0x0F00 ) >> 8 );
}

/// Reads byte value of Y on pattern vvYv.
inline Chip8::byte_t readY( const Chip8::word_t instr )
{
    return static_cast<Chip8::byte_t>( ( instr & 0x00F0 ) >> 4 );
}

/// Reads byte value of N on pattern vvvN.
inline Chip8::byte_t readN( const Chip8::word_t instr )
{
    return static_cast<Chip8::byte_t>( instr & 0x000F );
}

/// Reads byte value of NN on pattern vvNN.
inline Chip8::byte_t readNN( const Chip8::word_t instr )
{
    return static_cast<Chip8::byte_t>( instr & 0x00FF );
}

/// Reads word value of NNN on pattern vNNN.
inline Chip8::word_t readNNN( const Chip8::word_t instr )
{
    return instr & 0x0FFF;
}

} // namespace WordDecoder
} // namespace model
