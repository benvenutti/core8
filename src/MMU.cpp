#include "MMU.hpp"

#include <algorithm>
#include <iterator>
#include <limits>

namespace Core8 {

MMU::MMU() {
  clear();
}

bool MMU::operator==(const MMU& mmu) const {
  return m_memory == mmu.m_memory;
}

Chip8::BYTE MMU::readByte(const std::size_t address) const {
  const auto byte = m_memory.at(address);

  return byte;
}

Chip8::WORD MMU::readWord(const std::size_t address) const {
  const auto msb = m_memory.at(address) << std::numeric_limits<Chip8::BYTE>::digits;
  const auto lsb = m_memory.at(address + 1);

  return msb | lsb;
}

void MMU::writeByte(const Chip8::BYTE byte, const std::size_t address) {
  m_memory.at(address) = byte;
}

void MMU::load(const std::vector<Chip8::BYTE>& rom, const std::size_t address) {
  const auto availableMemory = m_memory.size() - address;
  const auto dataSize = rom.size();
  const auto length = std::min(availableMemory, dataSize);

  std::copy_n(std::begin(rom), length,
              std::begin(m_memory) + address);
}

void MMU::load(std::istream& rom, const std::size_t address) {
  std::noskipws(rom);

  const std::vector<Chip8::BYTE> data{std::istream_iterator<Chip8::BYTE>(rom),
                                      std::istream_iterator<Chip8::BYTE>()};

  load(data, address);
}

void MMU::clear() {
  m_memory.fill(0x0);
}

MMU::Memory::const_iterator MMU::begin() const {
  return std::cbegin(m_memory);
}

MMU::Memory::iterator MMU::begin() {
  return std::begin(m_memory);
}

MMU::Memory::const_iterator MMU::end() const {
  return std::cend(m_memory);
}

MMU::Memory::iterator MMU::end() {
  return std::end(m_memory);
}

} // namespace Core8