#pragma once

#include <model/RandomNumberGenerator.hpp>

#include <random>

namespace model
{

class MersenneByteTwister : public RandomNumberGenerator
{
public:
    MersenneByteTwister()           = default;
    ~MersenneByteTwister() override = default;

    unsigned short get() const override
    {
        return m_distribution( m_generator );
    }

private:
    mutable std::mt19937                                  m_generator{ std::random_device{}() };
    mutable std::uniform_int_distribution<unsigned short> m_distribution{ 0x00u, 0xFFu };
};

} // namespace model
