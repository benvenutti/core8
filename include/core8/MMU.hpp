#ifndef CORE8_MMU_H
#define CORE8_MMU_H

#include <array>
#include <istream>

#include "Chip8.hpp"

namespace Core8 {

/// @brief Big-endian memory management unit.
class MMU {
  public:
    MMU() = default;

    Chip8::BYTE readByte(const std::size_t address) const;
    Chip8::WORD readWord(const std::size_t address) const;

    void writeByte(const Chip8::BYTE byte, const std::size_t address);

    void load(std::istream& rom, const std::size_t address);
    void clear();

    constexpr std::size_t getSize() const noexcept {
      return memory.size();
    }

  private:
    std::array<Chip8::BYTE, Chip8::RAM_SIZE> memory;
};

} // namespace Core8

#endif