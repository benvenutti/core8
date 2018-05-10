#pragma once

#include <array>
#include <functional>
#include <map>

#include "Chip8.hpp"
#include "IoDevice.hpp"
#include "MMU.hpp"
#include "OpDecoder.hpp"
#include "RandomNumberGenerator.hpp"

namespace model
{

class CPU
{
public:
    CPU( MMU& mmu, IoDevice& ioDevice, RandomNumberGenerator& rndGenerator );

    void cycle();
    void execute( const Chip8::word_t instr );

    Chip8::byte_t readRegister( const Chip8::registers id ) const;
    void          writeRegister( const Chip8::registers id, const Chip8::byte_t value );
    void          loadToRegisters( const std::vector<Chip8::byte_t> values );

    Chip8::word_t getPc() const
    {
        return m_pc;
    }
    Chip8::byte_t getSp() const
    {
        return m_sp;
    };

    const std::array<Chip8::word_t, Chip8::stack_size>& getStack() const
    {
        return m_stack;
    }

    void setDelayTimer( const Chip8::byte_t delay )
    {
        m_delayTimer = delay;
    };
    Chip8::byte_t getDelayTimer() const
    {
        return m_delayTimer;
    };

    Chip8::byte_t getSoundTimer() const
    {
        return m_soundTimer;
    };

    void setInstruction( const Chip8::word_t instr )
    {
        m_instruction = instr;
    }
    Chip8::word_t getInstruction() const
    {
        return m_instruction;
    }

    void setI( const Chip8::word_t address )
    {
        m_I = address;
    }
    Chip8::word_t getI() const
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

    Chip8::word_t m_pc{ Chip8::init_rom_load_address };
    Chip8::word_t m_instruction{ 0u };
    Chip8::word_t m_I{ 0u };

    Chip8::opcode m_opcode{ Chip8::opcode::INVALID };

    Chip8::byte_t m_sp{ 0u };
    Chip8::byte_t m_delayTimer{ 0u };
    Chip8::byte_t m_soundTimer{ 0u };

    bool isInterrupted{ false };

    std::array<Chip8::byte_t, Chip8::num_registers> m_registers;
    std::array<Chip8::word_t, Chip8::stack_size>    m_stack;
    std::array<Chip8::byte_t, Chip8::display_size>  m_frameBuffer;

    MMU&                   m_mmu;
    IoDevice&              m_ioDevice;
    RandomNumberGenerator& m_rndGenerator;
};

} // namespace model
