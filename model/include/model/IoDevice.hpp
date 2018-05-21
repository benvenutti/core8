#pragma once

#include "Chip8.hpp"

#include <boost/optional.hpp>

namespace model
{

class IoDevice
{
public:
    virtual ~IoDevice() = default;

    virtual bool isKeyPressed( chip8::key key ) const = 0;

    virtual boost::optional<chip8::key> pressedKey() const = 0;
};

} // namespace model
