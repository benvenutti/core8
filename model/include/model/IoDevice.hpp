#pragma once

#include "Chip8.hpp"

namespace model
{

class IoDevice
{
public:
    virtual ~IoDevice() = default;

    virtual bool isKeyPressed( chip8::key key ) const = 0;

    // TODO use boost::optional and remove chip8::key::none
    virtual chip8::key pressedKey() const = 0;
};

} // namespace model
