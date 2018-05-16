#pragma once

#include <model/IoDevice.hpp>

#include <array>

class IoDeviceImpl : public model::IoDevice
{
public:
    IoDeviceImpl();
    ~IoDeviceImpl() override = default;

    bool isKeyPressed( model::chip8::key key ) const override;

    model::chip8::key getPressedKey() const override;

    void set( int key, bool pressed );

private:
    std::array<bool, 0x10> m_keypad = {};
};
