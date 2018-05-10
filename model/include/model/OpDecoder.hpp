#pragma once

#include "Chip8.hpp"

namespace Core8
{
namespace OpDecoder
{

Chip8::OpCode decode( const Chip8::WORD word );

} // namespace OpDecoder
} // namespace Core8
