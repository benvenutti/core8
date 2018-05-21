#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <iterator>

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

    template <typename T>
    void load( const T& rom, chip8::word_t address )
    {
        const auto romSize = static_cast<std::size_t>( std::distance( std::begin( rom ), std::end( rom ) ) );
        const auto length  = std::min( size() - address, romSize );

        std::copy_n( std::begin( rom ), length, std::begin( m_memory ) + address );
    }

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
    std::array<chip8::byte_t, chip8::ram_size> m_memory = {};
};

} // namespace model
