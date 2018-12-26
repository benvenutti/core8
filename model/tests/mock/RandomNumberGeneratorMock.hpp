#pragma once

#include "model/RandomNumberGenerator.hpp"

namespace Aux
{

class RandomNumberGeneratorMock : public model::RandomNumberGenerator
{
public:
    RandomNumberGeneratorMock()           = default;
    ~RandomNumberGeneratorMock() override = default;

    virtual model::chip8::byte_t get() override
    {
        return m_value;
    }

    void setValue( const model::chip8::byte_t value )
    {
        m_value = value;
    }

private:
    model::chip8::byte_t m_value{ 0u };
};

} // namespace Aux