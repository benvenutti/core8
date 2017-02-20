#include "MMU.hpp"

#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>

namespace Core8 {

bool MMU::operator==(const MMU& mmu) const {
  return memory == mmu.memory;
}

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

  const std::vector<Chip8::BYTE> data{std::istream_iterator<Chip8::BYTE>(rom),
                                      std::istream_iterator<Chip8::BYTE>()};

  const auto availableMemory = memory.size() - address;
  const auto dataSize = data.size();
  const auto length = std::min(availableMemory, dataSize);

  std::copy_n(std::begin(data), length,
              std::next(std::begin(memory), address));
}

void MMU::clear() {
  memory.fill(0x0);
}

} // namespace Core8