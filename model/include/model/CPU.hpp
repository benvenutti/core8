#pragma once

#include <array>
#include <functional>
#include <map>

#include "Chip8.hpp"
#include "IoDevice.hpp"
#include "MMU.hpp"
#include "OpDecoder.hpp"
#include "RandomNumberGenerator.hpp"

namespace Core8
{

class CPU
{
public:
    CPU( MMU& mmu, IoDevice& ioDevice, RandomNumberGenerator& rndGenerator );

    void cycle();
    void execute( const Chip8::WORD instr );

    Chip8::BYTE readRegister( const Chip8::Register id ) const;
    void        writeRegister( const Chip8::Register id, const Chip8::BYTE value );
    void        loadToRegisters( const std::vector<Chip8::BYTE> values );

    Chip8::WORD getPc() const
    {
        return m_pc;
    }
    Chip8::BYTE getSp() const
    {
        return m_sp;
    };

    const std::array<Chip8::WORD, Chip8::STACK_SIZE>& getStack() const
    {
        return m_stack;
    }

    void setDelayTimer( const Chip8::BYTE delay )
    {
        m_delayTimer = delay;
    };
    Chip8::BYTE getDelayTimer() const
    {
        return m_delayTimer;
    };

    Chip8::BYTE getSoundTimer() const
    {
        return m_soundTimer;
    };

    void setInstruction( const Chip8::WORD instr )
    {
        m_instruction = instr;
    }
    Chip8::WORD getInstruction() const
    {
        return m_instruction;
    }

    void setI( const Chip8::WORD address )
    {
        m_I = address;
    }
    Chip8::WORD getI() const
    {
        return m_I;
    }

private:
    void fetch();
    void decode();
    void execute();
    void updateDelayTimer();
    void updateSoundTimer();

    void clearDisplay();
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
    void loadNnnToI();
    void loadRegistersToI();
    void loadItoRegisters();
    void addVxToI();
    void loadFontSpriteAddressToI();
    void draw();
    void executeSkipIfVxIsPressed();
    void executeSkipIfVxIsNotPressed();
    void executeWaitPressedKeyToVx();
    void executeLoadVxBcdToI();
    void executeLoadRandomToVx();

    Chip8::WORD m_pc{ Chip8::INIT_ROM_LOAD_ADDRESS };
    Chip8::WORD m_instruction{ 0u };
    Chip8::WORD m_I{ 0u };

    Chip8::OpCode m_opcode{ Chip8::OpCode::INVALID };

    Chip8::BYTE m_sp{ 0u };
    Chip8::BYTE m_delayTimer{ 0u };
    Chip8::BYTE m_soundTimer{ 0u };

    bool isInterrupted{ false };

    std::array<Chip8::BYTE, Chip8::NUMBER_OF_REGISTERS> m_registers;
    std::array<Chip8::WORD, Chip8::STACK_SIZE>          m_stack;
    std::array<Chip8::BYTE, Chip8::DISPLAY_SIZE>        m_frameBuffer;

    MMU&                   m_mmu;
    IoDevice&              m_ioDevice;
    RandomNumberGenerator& m_rndGenerator;
};

} // namespace Core8
