#pragma once

#include "Chip8.hpp"

namespace Core8
{

class RandomNumberGenerator
{
public:
    virtual ~RandomNumberGenerator() = default;

    virtual Chip8::BYTE get() = 0;
};

} // namespace Core8
