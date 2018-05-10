#pragma once

#include "Chip8.hpp"

namespace model
{
namespace OpDecoder
{

chip8::opcode decode( const chip8::word_t word );

} // namespace OpDecoder
} // namespace model
