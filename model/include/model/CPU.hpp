#pragma once

#include "Chip8.hpp"
#include "IoDevice.hpp"
#include "MMU.hpp"
#include "RandomNumberGenerator.hpp"

#include <array>
#include <cstdint>

namespace model
{

class CPU
{
public:
    using VideoBuffer = std::array<std::uint32_t, chip8::display_size>;

    CPU( MMU& mmu, IoDevice& ioDevice, RandomNumberGenerator& rndGenerator );

    void cycle();
    void execute( chip8::word_t instr );

    chip8::byte_t readRegister( chip8::reg id ) const;
    void          writeRegister( chip8::reg id, chip8::byte_t value );
    void          loadToRegisters( const std::vector<chip8::byte_t> values );

    chip8::word_t getPc() const
    {
        return m_pc;
    }
    chip8::byte_t getSp() const
    {
        return m_sp;
    }

    const std::array<chip8::word_t, chip8::stack_size>& getStack() const
    {
        return m_stack;
    }

    void setDelayTimer( chip8::byte_t delay )
    {
        m_delayTimer = delay;
    }

    chip8::byte_t getDelayTimer() const
    {
        return m_delayTimer;
    }

    chip8::byte_t getSoundTimer() const
    {
        return m_soundTimer;
    }

    void setInstruction( chip8::word_t instr )
    {
        m_instruction = instr;
    }

    chip8::word_t getInstruction() const
    {
        return m_instruction;
    }

    void setI( chip8::word_t address )
    {
        m_I = address;
    }
    chip8::word_t getI() const
    {
        return m_I;
    }

    const VideoBuffer& buffer() const
    {
        return m_frameBuffer;
    }

    bool m_drawFlag = false;

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

    chip8::word_t m_pc{ chip8::init_rom_load_address };
    chip8::word_t m_instruction{ 0u };
    chip8::word_t m_I{ 0u };

    chip8::opcode m_opcode{ chip8::opcode::invalid };

    chip8::byte_t m_sp{ 0u };
    chip8::byte_t m_delayTimer{ 0u };
    chip8::byte_t m_soundTimer{ 0u };

    bool isInterrupted{ false };

    std::array<chip8::byte_t, chip8::num_registers> m_registers   = {};
    std::array<chip8::word_t, chip8::stack_size>    m_stack       = {};
    VideoBuffer                                     m_frameBuffer = {};

    MMU&                   m_mmu;
    IoDevice&              m_ioDevice;
    RandomNumberGenerator& m_rndGenerator;
};

} // namespace model
