#pragma once

#include <model/Chip8.hpp>
#include <model/IoDevice.hpp>

#include <optional>

namespace Mock
{

class IoDeviceMock : public model::IoDevice
{
public:
    ~IoDeviceMock() override = default;

    bool isKeyPressed( model::chip8::key key ) const override
    {
        if ( m_pressedKey )
        {
            return key == m_pressedKey.value();
        }

        return false;
    }

    std::optional< model::chip8::key > pressedKey() const override
    {
        return m_pressedKey;
    }

    void pressedKey( model::chip8::key key )
    {
        m_pressedKey = key;
    }

private:
    std::optional< model::chip8::key > m_pressedKey = std::nullopt;
};

} // namespace Mock
