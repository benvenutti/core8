#ifndef CORE8_CPU_HPP
#define CORE8_CPU_HPP

#include <array>

#include "Chip8.hpp"

namespace Core8 {

class CPU {
  public:
    CPU() = default;

    Chip8::BYTE readRegister(const Chip8::REGISTER id) const;
    void writeRegister(const Chip8::REGISTER id, const Chip8::BYTE value);

  private:
    std::array<Chip8::BYTE, Chip8::NUMBER_OF_REGISTERS> registers;
};

} // namespace Core8

#endif