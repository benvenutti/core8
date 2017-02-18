#ifndef CORE8_WORDDECODER_HPP
#define CORE8_WORDDECODER_HPP

#include "Chip8.hpp"

namespace Core8 {
namespace WordDecoder {

/// Reads byte value of X on pattern vXvv.
inline Chip8::BYTE readX(const Chip8::WORD instr) {
  return static_cast<Chip8::BYTE>((instr & 0x0F00) >> 8);
};

} // namespace WorDecoder
} // namespace Core8

#endif
