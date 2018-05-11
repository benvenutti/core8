#pragma once

#include <model/IoDevice.hpp>

class IoDeviceImpl : public model::IoDevice
{
public:
    IoDeviceImpl();
    ~IoDeviceImpl() override = default;

    void drawScreen( const std::array<model::chip8::byte_t, model::chip8::display_size>& frame ) override;

    bool isKeyPressed( const model::chip8::key key ) const override;

    model::chip8::key getPressedKey() const override;

private:
    // TODO ?
};
