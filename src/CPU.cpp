#include "CPU.hpp"

#include "WordDecoder.hpp"

namespace Core8 {

CPU::CPU(MMU& mmu, IoConnector& ioConnector)
    : m_mmu(mmu),
      m_ioConnector(ioConnector),
      m_dispatchTable{
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
        {Chip8::OPCODE::SKIP_IF_VX_IS_NOT_PRESSED, [this] () { executeSkipIfVxIsNotPressed(); }},
        {Chip8::OPCODE::LOAD_PRESSED_KEY_TO_VX, [this] () { executeWaitPressedKeyToVx(); }}
      }
{
}

Chip8::BYTE CPU::readRegister(const Chip8::REGISTER id) const {
  return m_registers[static_cast<std::size_t>(id)];
}

void CPU::writeRegister(const Chip8::REGISTER id, const Chip8::BYTE value) {
  m_registers[static_cast<std::size_t>(id)] = value;
}

void CPU::decode() {
  m_opcode = OpDecoder::decode(m_instruction);
}

void CPU::execute() {
  m_dispatchTable.at(m_opcode)();
}

void CPU::clearDisplay() {
  m_frameBuffer.fill(0x0);
}

void CPU::jumpToNnn() {
  m_pc = WordDecoder::readNNN(m_instruction);
}

void CPU::returnFromSubroutine() {
  m_pc = m_stack.at(--m_sp);
}

void CPU::callNNN() {
  m_stack.at(m_sp++) = m_pc;
  m_pc = WordDecoder::readNNN(m_instruction);
}

void CPU::skipIfVxEqualsNn() {
  const auto x = WordDecoder::readX(m_instruction);
  const auto nn = WordDecoder::readNN(m_instruction);

  if (m_registers.at(x) == nn) {
    m_pc += Chip8::INSTRUCTION_BYTE_SIZE;
  }
}

void CPU::skipIfVxNotEqualsNn() {
  const auto x = WordDecoder::readX(m_instruction);
  const auto nn = WordDecoder::readNN(m_instruction);

  if (m_registers.at(x) != nn) {
    m_pc += Chip8::INSTRUCTION_BYTE_SIZE;
  }
}

void CPU::skipIfVxEqualsVy() {
  const auto x = WordDecoder::readX(m_instruction);
  const auto y = WordDecoder::readY(m_instruction);

  if (m_registers.at(x) == m_registers.at(y)) {
    m_pc += Chip8::INSTRUCTION_BYTE_SIZE;
  }
}

void CPU::skipIfVxNotEqualsVy() {
  const auto x = WordDecoder::readX(m_instruction);
  const auto y = WordDecoder::readY(m_instruction);

  if (m_registers.at(x) != m_registers.at(y)) {
    m_pc += Chip8::INSTRUCTION_BYTE_SIZE;
  }
}

void CPU::loadNnToVx() {
  const auto x = WordDecoder::readX(m_instruction);
  const auto nn = WordDecoder::readNN(m_instruction);
  m_registers.at(x) = nn;
}

void CPU::addNnToVx() {
  const auto x = WordDecoder::readX(m_instruction);
  const auto nn = WordDecoder::readNN(m_instruction);
  m_registers.at(x) += nn;
}

void CPU::loadVyToVx() {
  const auto x = WordDecoder::readX(m_instruction);
  const auto y = WordDecoder::readY(m_instruction);
  m_registers.at(x) = m_registers.at(y);
}

void CPU::bitwiseVxOrVy() {
  const auto x = WordDecoder::readX(m_instruction);
  const auto y = WordDecoder::readY(m_instruction);
  m_registers.at(x) |= m_registers.at(y);
}

void CPU::bitwiseVxAndVy() {
  const auto x = WordDecoder::readX(m_instruction);
  const auto y = WordDecoder::readY(m_instruction);
  m_registers.at(x) &= m_registers.at(y);
}

void CPU::bitwiseVxXorVy() {
  const auto x = WordDecoder::readX(m_instruction);
  const auto y = WordDecoder::readY(m_instruction);
  m_registers.at(x) ^= m_registers.at(y);
}

void CPU::shiftVxRight() {
  const auto x = WordDecoder::readX(m_instruction);
  const auto mask = static_cast<Chip8::BYTE>(0x1);
  auto& vx = m_registers.at(x);

  writeRegister(Chip8::REGISTER::VF, vx & mask);
  vx >>= 1;
}

void CPU::shiftVxLeft() {
  const auto x = WordDecoder::readX(m_instruction);
  auto& vx = m_registers.at(x);
  writeRegister(Chip8::REGISTER::VF, vx >> 7);
  vx <<= 1;
}

void CPU::addVyToVx() {
  const auto x = WordDecoder::readX(m_instruction);
  const auto y = WordDecoder::readY(m_instruction);

  auto& vx = m_registers.at(x);
  const auto& vy = m_registers.at(y);

  const auto hasCarry = vy > (0xFF - vx);
  writeRegister(Chip8::REGISTER::VF, hasCarry ? 0x1 : 0x0);

  vx += vy;
}

void CPU::subVyFromVx() {
  const auto x = WordDecoder::readX(m_instruction);
  const auto y = WordDecoder::readY(m_instruction);

  auto& vx = m_registers.at(x);
  const auto& vy = m_registers.at(y);

  const auto hasBorrow = vy > vx;
  writeRegister(Chip8::REGISTER::VF, hasBorrow ? 0x0 : 0x1);

  vx -= vy;
}

void CPU::subVxFromVy() {
  const auto x = WordDecoder::readX(m_instruction);
  const auto y = WordDecoder::readY(m_instruction);

  auto& vx = m_registers.at(x);
  const auto& vy = m_registers.at(y);

  const auto hasBorrow = vx > vy;
  writeRegister(Chip8::REGISTER::VF, hasBorrow ? 0x0 : 0x1);

  vx = vy - vx;
}

void CPU::jumpToNnnPlusV0() {
  m_pc = WordDecoder::readNNN(m_instruction) + m_registers.at(0x0);
}

void CPU::loadDelayToVx() {
  const auto x = WordDecoder::readX(m_instruction);
  m_registers.at(x) = m_delayTimer;
}

void CPU::loadVxToDelay() {
  const auto x = WordDecoder::readX(m_instruction);
  m_delayTimer = m_registers.at(x);
}

void CPU::loadVxToSound() {
  const auto x = WordDecoder::readX(m_instruction);
  m_soundTimer = m_registers.at(x);
}

void CPU::loadNnnToI() {
  m_I = WordDecoder::readNNN(m_instruction);
}

void CPU::loadRegistersToI() {
  const auto x = WordDecoder::readX(m_instruction);

  for (std::size_t i = 0; i <= x; ++i) {
    m_mmu.writeByte(m_registers.at(i), m_I + i);
  }

  m_I += x + 1;
}

void CPU::loadItoRegisters() {
  const auto x = WordDecoder::readX(m_instruction);

  for (std::size_t i = 0; i <= x; ++i) {
    m_registers.at(i) = m_mmu.readByte(m_I + i);
  }

  m_I += x + 1;
}

void CPU::addVxToI() {
  const auto x = WordDecoder::readX(m_instruction);
  m_I += m_registers.at(x);
}

void CPU::loadFontSpriteAddressToI() {
  const auto x = WordDecoder::readX(m_instruction);
  m_I = m_registers.at(x) * Chip8::CHAR_SPRITE_SIZE;
}

void CPU::draw() {
  const auto vx = WordDecoder::readX(m_instruction);
  const auto vy = WordDecoder::readY(m_instruction);
  const auto x = m_registers.at(vx);
  const auto y = m_registers.at(vy);
  const auto height = WordDecoder::readN(m_instruction);

  Chip8::BYTE flipped{0x0u};

  for (auto line = 0u; line < height; ++line) {
    const auto rowPixels = m_mmu.readByte(m_I + line);

    for (auto row = 0; row < Chip8::SPRITE_WIDTH; ++row) {
      if ((rowPixels & (0x80 >> row)) != 0) {
        const auto offset = (x + row + ((y + line) * 64)) % 2048;
        Chip8::BYTE& pixel = m_frameBuffer.at(offset);
        flipped = pixel;
        pixel ^= 1u;
      }
    }
  }

  writeRegister(Chip8::REGISTER::VF, flipped);
}

void CPU::executeSkipIfVxIsPressed() {
  const auto x = WordDecoder::readX(m_instruction);
  const auto key = static_cast<Chip8::KEY>(m_registers.at(x));

  if (m_ioConnector.isKeyPressed(key)) {
    m_pc += Chip8::INSTRUCTION_BYTE_SIZE;
  }
}

void CPU::executeSkipIfVxIsNotPressed() {
  const auto x = WordDecoder::readX(m_instruction);
  const auto key = static_cast<Chip8::KEY>(m_registers.at(x));

  if (!m_ioConnector.isKeyPressed(key)) {
    m_pc += Chip8::INSTRUCTION_BYTE_SIZE;
  }
}

void CPU::executeWaitPressedKeyToVx() {
  const auto pressedKey = m_ioConnector.getPressedKey();

  if (pressedKey != Chip8::KEY::NONE) {
    const auto x = WordDecoder::readX(m_instruction);
    m_registers.at(x) = static_cast<Chip8::BYTE>(pressedKey);
    m_pc += Chip8::INSTRUCTION_BYTE_SIZE;
  }
}

} //namespace Core8