#pragma once

#include <model/IoDevice.hpp>

#include <array>

class IoDeviceImpl : public model::IoDevice
{
public:
    IoDeviceImpl();
    ~IoDeviceImpl() override = default;

    bool isKeyPressed( model::chip8::key key ) const override;

    boost::optional<model::chip8::key> pressedKey() const override;

    void set( int key, bool pressed );

private:
    std::array<bool, model::chip8::keypad_size> m_keypad = {};
};
