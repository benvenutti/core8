#pragma once

#include <array>

#include "Chip8.hpp"

namespace model
{

class IoDevice
{
public:
    virtual ~IoDevice() = default;

    virtual bool isKeyPressed( const chip8::key key ) const = 0;

    virtual chip8::key getPressedKey() const = 0;
};

} // namespace model
