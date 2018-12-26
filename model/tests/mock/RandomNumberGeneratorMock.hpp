#pragma once

#include "model/RandomNumberGenerator.hpp"

namespace Mock
{

class RandomNumberGeneratorMock : public model::RandomNumberGenerator
{
public:
    RandomNumberGeneratorMock()           = default;
    ~RandomNumberGeneratorMock() override = default;

    virtual unsigned short get() const override
    {
        return m_value;
    }

    void setValue( unsigned short value )
    {
        m_value = value;
    }

private:
    unsigned short m_value{ 0u };
};

} // namespace Mock
