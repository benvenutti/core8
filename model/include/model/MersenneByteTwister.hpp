#pragma once

#include <random>

namespace model
{

class MersenneByteTwister : public RandomNumberGenerator
{
public:
    MersenneByteTwister()           = default;
    ~MersenneByteTwister() override = default;

    chip8::byte_t get() override
    {
        return m_distribution( m_generator );
    }

private:
    std::mt19937                                 m_generator{ std::random_device{}() };
    std::uniform_int_distribution<chip8::byte_t> m_distribution{ 0x01, 0xFF };
};

} // namespace model
