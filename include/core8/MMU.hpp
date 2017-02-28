#ifndef CORE8_MMU_H
#define CORE8_MMU_H

#include <array>
#include <istream>
#include <vector>

#include "Chip8.hpp"

namespace Core8 {

/// @brief Big-endian memory management unit.
class MMU {
  public:
    MMU() = default;
    MMU(const MMU& mmu) = default;

    bool operator==(const MMU& mmu) const;

    Chip8::BYTE readByte(const std::size_t address) const;
    Chip8::WORD readWord(const std::size_t address) const;

    void writeByte(const Chip8::BYTE byte, const std::size_t address);

    void load(const std::vector<Chip8::BYTE>& rom, const std::size_t address);
    void load(std::istream& rom, const std::size_t address);

    void clear();

    constexpr std::size_t getSize() const noexcept {
      return m_memory.size();
    }

  private:
    std::array<Chip8::BYTE, Chip8::RAM_SIZE> m_memory;
};

} // namespace Core8

#endif