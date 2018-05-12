#pragma once

#include <model/IoDevice.hpp>

class IoDeviceImpl : public model::IoDevice
{
public:
    IoDeviceImpl();
    ~IoDeviceImpl() override = default;

    bool isKeyPressed( model::chip8::key key ) const override;

    model::chip8::key getPressedKey() const override;
};
