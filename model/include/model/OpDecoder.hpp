#pragma once

#include "Chip8.hpp"

namespace Core8
{
namespace OpDecoder
{

Chip8::opcode decode( const Chip8::word_t word );

} // namespace OpDecoder
} // namespace Core8
