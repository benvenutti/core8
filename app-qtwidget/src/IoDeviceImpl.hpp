#pragma once

#include <model/IoDevice.hpp>

#include <array>
#include <optional>

class IoDeviceImpl : public model::IoDevice
{
public:
    IoDeviceImpl()           = default;
    ~IoDeviceImpl() override = default;

    bool isKeyPressed( model::chip8::key key ) const override;

    std::optional<model::chip8::key> pressedKey() const override;

    void set( int key, bool pressed );

private:
    std::array<bool, model::chip8::keypad_size> m_keypad = {};
};
