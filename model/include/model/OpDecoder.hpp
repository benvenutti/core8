#ifndef CORE8_OPDECODER_H
#define CORE8_OPDECODER_H

#include "Chip8.hpp"

namespace Core8
{
namespace OpDecoder
{

Chip8::OpCode decode( const Chip8::WORD word );

} // namespace OpDecoder
} // namespace Core8

#endif
