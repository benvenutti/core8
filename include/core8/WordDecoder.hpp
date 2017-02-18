#ifndef CORE8_WORDDECODER_HPP
#define CORE8_WORDDECODER_HPP

#include "Chip8.hpp"

namespace Core8 {
namespace WordDecoder {

/// Reads byte value of X on pattern vXvv.
inline Chip8::BYTE readX(const Chip8::WORD instr) {
  return static_cast<Chip8::BYTE>((instr & 0x0F00) >> 8);
};

/// Reads byte value of Y on pattern vvYv.
inline Chip8::BYTE readY(const Chip8::WORD instr) {
  return static_cast<Chip8::BYTE>((instr & 0x00F0) >> 4);
};

/// Reads byte value of N on pattern vvvN.
inline Chip8::BYTE readN(const Chip8::WORD instr) {
  return static_cast<Chip8::BYTE>(instr & 0x000F);
};

} // namespace WorDecoder
} // namespace Core8

#endif
