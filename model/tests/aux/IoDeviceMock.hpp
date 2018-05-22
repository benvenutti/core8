#pragma once

#include "Chip8.hpp"
#include "IoDevice.hpp"

namespace Aux
{

class IoDeviceMock : public model::IoDevice
{
public:
    ~IoDeviceMock() override = default;

    bool isKeyPressed( model::chip8::key key ) const override
    {
        if ( m_pressedKey )
        {
            return key == m_pressedKey.get();
        }

        return false;
    }

    boost::optional<model::chip8::key> pressedKey() const override
    {
        return m_pressedKey;
    }

    void pressedKey( model::chip8::key key )
    {
        m_pressedKey = key;
    }

private:
    boost::optional<model::chip8::key> m_pressedKey = boost::none;
};

} // namespace Aux
