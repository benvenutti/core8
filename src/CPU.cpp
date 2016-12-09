#include "CPU.hpp"

namespace Core8 {

/// Auxiliary functions for the CPU's operations
namespace {

template <typename T>
T mask(const int value) {
  return static_cast<T>(value);
}

/// Reads byte value of X on pattern vXvv.
inline Chip8::BYTE readX(const Chip8::WORD instr) {
  return static_cast<Chip8::BYTE>((instr & 0x0F00) >> 8);
};

/// Reads byte value of Y on pattern vvYv.
inline Chip8::BYTE readY(const Chip8::WORD instr) {
  return static_cast<Chip8::BYTE>((instr & 0x00F0) >> 4);
};

/// Reads byte value of NN on pattern vvNN.
inline Chip8::BYTE readNN(const Chip8::WORD instr) {
  return static_cast<Chip8::BYTE>(instr & 0x00FF);
};

} // unnamed namespace

CPU::CPU()
    : dispatchTable{
      {Chip8::OPCODE::SKIP_IF_VX_EQUALS_NN, [this] () { skipIfVxEqualsNn(); }},
      {Chip8::OPCODE::SKIP_IF_VX_NOT_EQUALS_NN, [this] () { skipIfVxNotEqualsNn(); }},
      {Chip8::OPCODE::SKIP_IF_VX_EQUALS_VY, [this] () { skipIfVxEqualsVy(); }},
      {Chip8::OPCODE::SKIP_IF_VX_NOT_EQUALS_VY, [this] () { skipIfVxNotEqualsVy(); }},
      {Chip8::OPCODE::LOAD_NN_TO_VX, [this] () { loadNnToVx(); }},
      {Chip8::OPCODE::ADD_NN_TO_VX, [this] () { addNnToVx(); }},
      {Chip8::OPCODE::LOAD_VY_TO_VX, [this] () { loadVyToVx(); }},
      {Chip8::OPCODE::VX_OR_VY, [this] () { bitwiseVxOrVy(); }},
      {Chip8::OPCODE::VX_AND_VY, [this] () { bitwiseVxAndVy(); }},
      {Chip8::OPCODE::VX_XOR_VY, [this] () { bitwiseVxXorVy(); }},
      {Chip8::OPCODE::SHIFT_VX_RIGHT, [this] () { shiftVxRight(); }},
      {Chip8::OPCODE::SHIFT_VX_LEFT, [this] () { shiftVxLeft(); }},
      {Chip8::OPCODE::VX_PLUS_VY, [this] () { addVyToVx(); }},
      {Chip8::OPCODE::VX_MINUS_VY, [this] () { subVyFromVx(); }}
    }
{
}

Chip8::BYTE CPU::readRegister(const Chip8::REGISTER id) const {
  return registers[static_cast<std::size_t>(id)];
}

void CPU::writeRegister(const Chip8::REGISTER id, const Chip8::BYTE value) {
  registers[static_cast<std::size_t>(id)] = value;
}

void CPU::decode() {
  opcode = OpDecoder::decode(instruction);
}

void CPU::execute() {
  dispatchTable.at(opcode)();
}

void CPU::skipIfVxEqualsNn() {
  const auto x = readX(instruction);
  const auto nn = readNN(instruction);

  if (registers.at(x) == nn) {
    pc += Chip8::INSTRUCTION_BYTE_SIZE;
  }
}

void CPU::skipIfVxNotEqualsNn() {
  const auto x = readX(instruction);
  const auto nn = readNN(instruction);

  if (registers.at(x) != nn) {
    pc += Chip8::INSTRUCTION_BYTE_SIZE;
  }
}

void CPU::skipIfVxEqualsVy() {
  const auto x = readX(instruction);
  const auto y = readY(instruction);

  if (registers.at(x) == registers.at(y)) {
    pc += Chip8::INSTRUCTION_BYTE_SIZE;
  }
}

void CPU::skipIfVxNotEqualsVy() {
  const auto x = readX(instruction);
  const auto y = readY(instruction);

  if (registers.at(x) != registers.at(y)) {
    pc += Chip8::INSTRUCTION_BYTE_SIZE;
  }
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

void CPU::loadVyToVx() {
  const auto x = readX(instruction);
  const auto y = readY(instruction);
  registers.at(x) = registers.at(y);
}

void CPU::bitwiseVxOrVy() {
  const auto x = readX(instruction);
  const auto y = readY(instruction);
  registers.at(x) |= registers.at(y);
}

void CPU::bitwiseVxAndVy() {
  const auto x = readX(instruction);
  const auto y = readY(instruction);
  registers.at(x) &= registers.at(y);
}

void CPU::bitwiseVxXorVy() {
  const auto x = readX(instruction);
  const auto y = readY(instruction);
  registers.at(x) ^= registers.at(y);
}

void CPU::shiftVxRight() {
  const auto x = readX(instruction);
  auto& vx = registers.at(x);
  writeRegister(Chip8::REGISTER::VF, vx & mask<Chip8::BYTE>(0x1));
  vx >>= 1;
}

void CPU::shiftVxLeft() {
  const auto x = readX(instruction);
  auto& vx = registers.at(x);
  writeRegister(Chip8::REGISTER::VF, vx >> 7);
  vx <<= 1;
}

void CPU::addVyToVx() {
  const auto x = readX(instruction);
  const auto y = readY(instruction);

  auto& vx = registers.at(x);
  const auto& vy = registers.at(y);

  const auto hasCarry = vy > (0xFF - vx);
  writeRegister(Chip8::REGISTER::VF, hasCarry ? 0x1 : 0x0);

  vx += vy;
}

void CPU::subVyFromVx() {
  const auto x = readX(instruction);
  const auto y = readY(instruction);

  auto& vx = registers.at(x);
  const auto& vy = registers.at(y);

  const auto hasBorrow = vy > vx;
  writeRegister(Chip8::REGISTER::VF, hasBorrow ? 0x0 : 0x1);

  vx -= vy;
}

} //namespace Core8