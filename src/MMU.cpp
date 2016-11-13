#include "MMU.hpp"

#include <iterator>
#include <limits>

namespace Core8 {

MMU::MMU(std::array<Chip8::BYTE, Chip8::RAM_SIZE>& memory)
    : memory{memory} {}

Chip8::BYTE MMU::readByte(const std::size_t address) const {
  const auto byte = memory.at(address);

  return byte;
}

Chip8::WORD MMU::readWord(const std::size_t address) const {
  const auto msb = memory.at(address) << std::numeric_limits<Chip8::BYTE>::digits;
  const auto lsb = memory.at(address + 1);

  return msb | lsb;
}

void MMU::writeByte(const Chip8::BYTE byte, const std::size_t address) {
  memory.at(address) = byte;
}

void MMU::load(std::istream& rom, const std::size_t address) {
  std::noskipws(rom);

  std::copy(std::istream_iterator<Chip8::BYTE>(rom),
            std::istream_iterator<Chip8::BYTE>(),
            &memory.at(address));
}

void MMU::clear() {
  memory.fill(0x0);
}

} // namespace Core8