#pragma once

namespace model
{

class RandomNumberGenerator
{
public:
    virtual ~RandomNumberGenerator() = default;

    virtual unsigned short get() const = 0;
};

} // namespace model
