#pragma once

#include <array>
#include <istream>
#include <vector>

#include "Chip8.hpp"

namespace Core8
{

/// @brief Big-endian memory management unit.
class MMU
{
public:
    MMU();

    bool operator==( const MMU& mmu ) const;

    Chip8::byte_t readByte( const std::size_t address ) const;
    Chip8::word_t readWord( const std::size_t address ) const;

    void writeByte( const Chip8::byte_t byte, const std::size_t address );

    void load( const std::vector<Chip8::byte_t>& rom, const std::size_t address );
    void load( std::istream& rom, const std::size_t address );

    void clear();

    std::size_t getSize() const noexcept
    {
        return m_memory.size();
    }

    using Memory = std::array<Chip8::byte_t, Chip8::ram_size>;

    Memory::const_iterator begin() const;
    Memory::iterator       begin();
    Memory::const_iterator end() const;
    Memory::iterator       end();

private:
    std::array<Chip8::byte_t, Chip8::ram_size> m_memory;
};

} // namespace Core8
