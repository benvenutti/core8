#pragma once

#include <model/Chip8.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <iterator>

namespace model
{

/// @brief Big-endian memory management unit.
class MMU
{
public:
    MMU() = default;

    bool operator==( const MMU& mmu ) const
    {
        return m_memory == mmu.m_memory;
    }

    chip8::byte_t readByte( chip8::word_t address ) const
    {
        return m_memory[address];
    }

    chip8::word_t readWord( chip8::word_t address ) const
    {
        const auto msb = m_memory[address] << std::numeric_limits<chip8::byte_t>::digits;
        const auto lsb = m_memory[address + 1];

        return msb | lsb;
    }

    void writeByte( chip8::byte_t byte, chip8::word_t address )
    {
        m_memory[address] = byte;
    }

    template <typename T>
    void load( const T& rom, chip8::word_t address )
    {
        const auto length = std::min( size() - address, std::size( rom ) );

        std::copy_n( std::begin( rom ), length, std::begin( m_memory ) + address );
    }

    void clear()
    {
        m_memory = {};
    }

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
