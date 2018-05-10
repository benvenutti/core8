#pragma once

#include <array>
#include <istream>
#include <vector>

#include "Chip8.hpp"

namespace model
{

/// @brief Big-endian memory management unit.
class MMU
{
public:
    MMU() = default;

    bool operator==( const MMU& mmu ) const;

    chip8::byte_t readByte( chip8::word_t address ) const;
    chip8::word_t readWord( chip8::word_t address ) const;

    void writeByte( chip8::byte_t byte, chip8::word_t address );

    void load( const std::vector<chip8::byte_t>& rom, chip8::word_t address );
    void load( std::istream& rom, chip8::word_t address );

    void clear();

    constexpr std::size_t size() const noexcept
    {
        return m_memory.size();
    }

    auto begin() const
    {
        return std::begin( m_memory );
    }

    auto begin()
    {
        return std::begin( m_memory );
    }

    auto end() const
    {
        return std::end( m_memory );
    }

    auto end()
    {
        return std::end( m_memory );
    }

private:
    std::array<chip8::byte_t, chip8::ram_size> m_memory{};
};

} // namespace model
