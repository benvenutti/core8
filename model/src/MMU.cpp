#include "MMU.hpp"

#include <limits>

namespace model
{

bool MMU::operator==( const MMU& mmu ) const
{
    return m_memory == mmu.m_memory;
}

chip8::byte_t MMU::readByte( chip8::word_t address ) const
{
    return m_memory[address];
}

chip8::word_t MMU::readWord( chip8::word_t address ) const
{
    const auto msb = m_memory[address] << std::numeric_limits<chip8::byte_t>::digits;
    const auto lsb = m_memory[address + 1];

    return msb | lsb;
}

void MMU::writeByte( chip8::byte_t byte, chip8::word_t address )
{
    m_memory[address] = byte;
}

void MMU::clear()
{
    m_memory = {};
}

} // namespace model
