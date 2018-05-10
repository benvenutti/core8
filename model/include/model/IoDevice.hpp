#pragma once

#include <array>

#include "Chip8.hpp"

namespace Core8
{

class IoDevice
{
public:
    virtual ~IoDevice() = default;

    virtual void drawScreen( const std::array<Chip8::byte_t, Chip8::display_size>& frame ) = 0;

    virtual bool isKeyPressed( const Chip8::key key ) const = 0;

    virtual Chip8::key getPressedKey() const = 0;
};

} // namespace Core8
