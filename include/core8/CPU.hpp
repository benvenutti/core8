#ifndef CORE8_CPU_HPP
#define CORE8_CPU_HPP

#include <array>
#include <functional>
#include <map>

#include "Chip8.hpp"
#include "OpDecoder.hpp"

namespace Core8 {

class CPU {
  public:
    CPU();

    Chip8::BYTE readRegister(const Chip8::REGISTER id) const;
    void writeRegister(const Chip8::REGISTER id, const Chip8::BYTE value);

    void setInstruction(const Chip8::WORD instr) { instruction = instr; }

    void decode();
    void execute();

  private:
    void loadNnToVx();
    void addNnToVx();

    Chip8::WORD instruction{0u};
    Chip8::OPCODE opcode{Chip8::OPCODE::INVALID};

    std::array<Chip8::BYTE, Chip8::NUMBER_OF_REGISTERS> registers;
    const std::map<Chip8::OPCODE, std::function<void(void)>> dispatchTable;
};

} // namespace Core8

#endif