#pragma once

#include "Chip8.hpp"
#include "IoDevice.hpp"

namespace Aux
{

class IoDeviceMock : public model::IoDevice
{
public:
    bool isKeyPressed( model::chip8::key key ) const override
    {
        return key == m_pressedKey;
    }

    model::chip8::key pressedKey() const override
    {
        return m_pressedKey;
    }

    void setPressedKey( model::chip8::key key )
    {
        m_pressedKey = key;
    }

private:
    model::chip8::key m_pressedKey{ model::chip8::key::none };
};

} // namespace Aux
