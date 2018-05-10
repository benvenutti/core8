#include "MMU.hpp"

#include <algorithm>
#include <iterator>
#include <limits>

namespace model
{

MMU::MMU()
{
    clear();
}

bool MMU::operator==( const MMU& mmu ) const
{
    return m_memory == mmu.m_memory;
}

Chip8::byte_t MMU::readByte( const std::size_t address ) const
{
    const auto byte = m_memory.at( address );

    return byte;
}

Chip8::word_t MMU::readWord( const std::size_t address ) const
{
    const auto msb = m_memory.at( address ) << std::numeric_limits<Chip8::byte_t>::digits;
    const auto lsb = m_memory.at( address + 1 );

    return msb | lsb;
}

void MMU::writeByte( const Chip8::byte_t byte, const std::size_t address )
{
    m_memory.at( address ) = byte;
}

void MMU::load( const std::vector<Chip8::byte_t>& rom, const std::size_t address )
{
    const auto availableMemory = m_memory.size() - address;
    const auto dataSize        = rom.size();
    const auto length          = std::min( availableMemory, dataSize );

    std::copy_n( std::begin( rom ), length, std::begin( m_memory ) + address );
}

void MMU::load( std::istream& rom, const std::size_t address )
{
    std::noskipws( rom );

    const std::vector<Chip8::byte_t> data{ std::istream_iterator<Chip8::byte_t>( rom ),
                                           std::istream_iterator<Chip8::byte_t>() };

    load( data, address );
}

void MMU::clear()
{
    m_memory.fill( 0x0 );
}

MMU::Memory::const_iterator MMU::begin() const
{
    return std::begin( m_memory );
}

MMU::Memory::iterator MMU::begin()
{
    return std::begin( m_memory );
}

MMU::Memory::const_iterator MMU::end() const
{
    return std::end( m_memory );
}

MMU::Memory::iterator MMU::end()
{
    return std::end( m_memory );
}

} // namespace model
