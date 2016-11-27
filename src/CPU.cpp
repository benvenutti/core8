#include "CPU.hpp"

#include "OpDecoder.hpp"

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

/// Auxiliary functions for the CPU's operations
namespace {

/// Reads byte value of X on pattern vXvv.
inline Chip8::BYTE readX(const Chip8::WORD instr) {
  return static_cast<Chip8::BYTE>((instr & 0x0F00) >> 8);
};

/// Reads byte value of NN on pattern vvNN.
inline Chip8::BYTE readNN(const Chip8::WORD instr) {
  return static_cast<Chip8::BYTE>(instr & 0x00FF);
};

} // unnamed namespace

void CPU::execute() {
  const auto opcode = OpDecoder::decode(instruction);
  dispatchTable.at(opcode)();
}

void CPU::loadNnToVx() {
  const auto x = readX(instruction);
  const auto nn = readNN(instruction);
  registers.at(x) = nn;
}

void CPU::addNnToVx() {
  const auto x = readX(instruction);
  const auto nn = readNN(instruction);
  registers.at(x) += nn;
}

} //namespace Core8