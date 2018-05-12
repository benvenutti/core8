#include "IoDeviceImpl.hpp"

IoDeviceImpl::IoDeviceImpl()
{
}

bool IoDeviceImpl::isKeyPressed( model::chip8::key ) const
{
    // TODO
    return false;
}

model::chip8::key IoDeviceImpl::getPressedKey() const
{
    // TODO
    return model::chip8::key::none;
}
