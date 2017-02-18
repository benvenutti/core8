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

/// Reads byte value of NN on pattern vvvN.
inline Chip8::BYTE readN(const Chip8::WORD instr) {
  return static_cast<Chip8::BYTE>(instr & 0x000F);
};

/// Reads byte value of NN on pattern vvNN.
inline Chip8::BYTE readNN(const Chip8::WORD instr) {
  return static_cast<Chip8::BYTE>(instr & 0x00FF);
};

/// Reads word value of NNN on pattern vNNN.
inline Chip8::WORD readNNN(const Chip8::WORD instr) {
  return static_cast<Chip8::WORD>(instr & 0x0FFF);
};

} // unnamed namespace

CPU::CPU(MMU& mmu, IoConnector& ioConnector)
    : mmu(mmu),
      ioConnector(ioConnector),
      dispatchTable{
        {Chip8::OPCODE::CLEAR_SCREEN, [this] () { clearDisplay(); }},
        {Chip8::OPCODE::JUMP, [this] () { jumpToNnn(); }},
        {Chip8::OPCODE::RETURN, [this] () { returnFromSubroutine(); }},
        {Chip8::OPCODE::CALL, [this] () { callNNN(); }},
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
        {Chip8::OPCODE::VX_MINUS_VY, [this] () { subVyFromVx(); }},
        {Chip8::OPCODE::SET_VX_TO_VY_MINUS_VX, [this] () { subVxFromVy(); }},
        {Chip8::OPCODE::JUMP_NNN_PLUS_V0, [this] () { jumpToNnnPlusV0(); }},
        {Chip8::OPCODE::LOAD_DELAY_TIMER_TO_VX, [this] () { loadDelayToVx(); }},
        {Chip8::OPCODE::LOAD_VX_TO_DELAY_TIMER, [this] () { loadVxToDelay(); }},
        {Chip8::OPCODE::LOAD_VX_TO_SOUND_TIMER, [this] () { loadVxToSound(); }},
        {Chip8::OPCODE::LOAD_NNN_TO_I, [this] () { loadNnnToI(); }},
        {Chip8::OPCODE::LOAD_V0_TO_VX_IN_ADDRESS_I, [this] () { loadRegistersToI(); }},
        {Chip8::OPCODE::LOAD_ADDRESS_I_TO_V0_TO_VX, [this] () { loadItoRegisters(); }},
        {Chip8::OPCODE::ADD_VX_TO_I, [this] () { addVxToI(); }},
        {Chip8::OPCODE::LOAD_FONT_SPRITE_ADDRESS_TO_I, [this] () { loadFontSpriteAddressToI(); }},
        {Chip8::OPCODE::DRAW, [this]() { draw(); }},
        {Chip8::OPCODE::SKIP_IF_VX_IS_PRESSED, [this] () { executeSkipIfVxIsPressed(); }},
        {Chip8::OPCODE::SKIP_IF_VX_IS_NOT_PRESSED, [this] () { executeSkipIfVxIsNotPressed(); }}
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

void CPU::clearDisplay() {
  frameBuffer.fill(0x0);
}

void CPU::jumpToNnn() {
  pc = readNNN(instruction);
}

void CPU::returnFromSubroutine() {
  pc = stack.at(--sp);
}

void CPU::callNNN() {
  stack.at(sp++) = pc;
  pc = readNNN(instruction);
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

void CPU::subVxFromVy() {
  const auto x = readX(instruction);
  const auto y = readY(instruction);

  auto& vx = registers.at(x);
  const auto& vy = registers.at(y);

  const auto hasBorrow = vx > vy;
  writeRegister(Chip8::REGISTER::VF, hasBorrow ? 0x0 : 0x1);

  vx = vy - vx;
}

void CPU::jumpToNnnPlusV0() {
  pc = readNNN(instruction) + registers.at(0x0);
}

void CPU::loadDelayToVx() {
  const auto x = readX(instruction);
  registers.at(x) = delayTimer;
}

void CPU::loadVxToDelay() {
  const auto x = readX(instruction);
  delayTimer = registers.at(x);
}

void CPU::loadVxToSound() {
  const auto x = readX(instruction);
  soundTimer = registers.at(x);
}

void CPU::loadNnnToI() {
  I = readNNN(instruction);
}

void CPU::loadRegistersToI() {
  const auto x = readX(instruction);

  for (std::size_t i = 0; i <= x; ++i) {
    mmu.writeByte(registers.at(i), I + i);
  }

  I += x + 1;
}

void CPU::loadItoRegisters() {
  const auto x = readX(instruction);

  for (std::size_t i = 0; i <= x; ++i) {
    registers.at(i) = mmu.readByte(I + i);
  }

  I += x + 1;
}

void CPU::addVxToI() {
  const auto x = readX(instruction);
  I += registers.at(x);
}

void CPU::loadFontSpriteAddressToI() {
  const auto x = readX(instruction);
  I = registers.at(x) * Chip8::CHAR_SPRITE_SIZE;
}

void CPU::draw() {
  const auto vx = readX(instruction);
  const auto vy = readY(instruction);
  const auto x = registers.at(vx);
  const auto y = registers.at(vy);
  const auto height = readN(instruction);

  Chip8::BYTE flipped{0x0u};

  for (auto line = 0u; line < height; ++line) {
    const auto rowPixels = mmu.readByte(I + line);

    for (auto row = 0; row < Chip8::SPRITE_WIDTH; ++row) {
      if ((rowPixels & (0x80 >> row)) != 0) {
        const auto offset = (x + row + ((y + line) * 64)) % 2048;
        Chip8::BYTE& pixel = frameBuffer.at(offset);
        flipped = pixel;
        pixel ^= 1u;
      }
    }
  }

  writeRegister(Chip8::REGISTER::VF, flipped);
}

void CPU::executeSkipIfVxIsPressed() {
  const auto x = readX(instruction);
  const auto key = static_cast<Chip8::KEY>(registers.at(x));

  if (ioConnector.isKeyPressed(key)) {
    pc += 2;
  }
}

void CPU::executeSkipIfVxIsNotPressed() {
  const auto x = readX(instruction);
  const auto key = static_cast<Chip8::KEY>(registers.at(x));

  if (!ioConnector.isKeyPressed(key)) {
    pc += 2;
  }
}

} //namespace Core8