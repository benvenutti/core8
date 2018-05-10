#pragma once

#include <array>

#include "Chip8.hpp"

namespace model
{

class IoDevice
{
public:
    virtual ~IoDevice() = default;

    virtual void drawScreen( const std::array<chip8::byte_t, chip8::display_size>& frame ) = 0;

    virtual bool isKeyPressed( const chip8::key key ) const = 0;

    virtual chip8::key getPressedKey() const = 0;
};

} // namespace model
