#include "IoDeviceImpl.hpp"

IoDeviceImpl::IoDeviceImpl()
{
}

void IoDeviceImpl::drawScreen( const std::array<model::chip8::byte_t, model::chip8::display_size>& )
{
    // TODO
}

bool IoDeviceImpl::isKeyPressed( const model::chip8::key ) const
{
    // TODO
    return false;
}

model::chip8::key IoDeviceImpl::getPressedKey() const
{
    // TODO
    return model::chip8::key::none;
}
