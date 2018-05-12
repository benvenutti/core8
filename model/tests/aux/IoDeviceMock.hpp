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
        return key == pressedKey;
    }

    model::chip8::key getPressedKey() const override
    {
        return pressedKey;
    }

    void setPressedKey( model::chip8::key key )
    {
        pressedKey = key;
    }

private:
    model::chip8::key pressedKey{ model::chip8::key::none };
};

} // namespace Aux
