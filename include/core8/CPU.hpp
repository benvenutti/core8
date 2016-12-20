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

    void decode();
    void execute();

    Chip8::BYTE readRegister(const Chip8::REGISTER id) const;
    void writeRegister(const Chip8::REGISTER id, const Chip8::BYTE value);

    Chip8::WORD getPc() const { return pc; }
    Chip8::BYTE getSp() const { return sp; };

    const std::array<Chip8::WORD, Chip8::STACK_SIZE>& getStack() const { return stack; }

    void setDelayTimer(const Chip8::BYTE delay) { delayTimer = delay; };
    Chip8::BYTE getDelayTimer() const { return delayTimer; };

    Chip8::BYTE getSoundTimer() const { return soundTimer; };

    void setInstruction(const Chip8::WORD instr) { instruction = instr; }

  private:
    void jumpToNnn();
    void returnFromSubroutine();
    void callNNN();
    void skipIfVxEqualsNn();
    void skipIfVxNotEqualsNn();
    void skipIfVxEqualsVy();
    void skipIfVxNotEqualsVy();
    void loadNnToVx();
    void addNnToVx();
    void loadVyToVx();
    void bitwiseVxOrVy();
    void bitwiseVxAndVy();
    void bitwiseVxXorVy();
    void shiftVxRight();
    void shiftVxLeft();
    void addVyToVx();
    void subVyFromVx();
    void subVxFromVy();
    void jumpToNnnPlusV0();
    void loadDelayToVx();
    void loadVxToDelay();
    void loadVxToSound();

    Chip8::WORD pc{Chip8::INIT_ROM_LOAD_ADDRESS};
    Chip8::WORD instruction{0u};

    Chip8::OPCODE opcode{Chip8::OPCODE::INVALID};

    Chip8::BYTE sp{0u};
    Chip8::BYTE delayTimer{0u};
    Chip8::BYTE soundTimer{0u};

    std::array<Chip8::BYTE, Chip8::NUMBER_OF_REGISTERS> registers;
    std::array<Chip8::WORD, Chip8::STACK_SIZE> stack;

    const std::map<Chip8::OPCODE, std::function<void(void)>> dispatchTable;
};

} // namespace Core8

#endif