#pragma once

#include <random>

#include "Chip8.hpp"

namespace model
{

class MersenneByteTwister : public RandomNumberGenerator
{
public:
    MersenneByteTwister()           = default;
    ~MersenneByteTwister() override = default;

    Chip8::byte_t get() override
    {
        return m_distribution( m_generator );
    }

private:
    std::mt19937                                 m_generator{ std::random_device{}() };
    std::uniform_int_distribution<Chip8::byte_t> m_distribution{ 0x01, 0xFF };
};

} // namespace model
