#include "CPU.hpp"

namespace Core8 {

CPU::CPU()
: dispatchTable{
    {Chip8::OPCODE::LOAD_NN_TO_VX, [this] () { loadNnToVx(); }},
    {Chip8::OPCODE::ADD_NN_TO_VX, [this] () { addNnToVx(); }}
  }
{
}

Chip8::BYTE CPU::readRegister(const Chip8::REGISTER id) const {
  return registers[static_cast<std::size_t>(id)];
}

void CPU::writeRegister(const Chip8::REGISTER id, const Chip8::BYTE value) {
  registers[static_cast<std::size_t>(id)] = value;
}

void CPU::loadNnToVx() {
}

void CPU::addNnToVx() {
}

} //namespace Core8