#pragma once

#include <model/IoDevice.hpp>

// TODO ?
#include <QKeyEvent>

#include <array>

class IoDeviceImpl : public model::IoDevice
{
public:
    IoDeviceImpl();
    ~IoDeviceImpl() override = default;

    bool isKeyPressed( model::chip8::key key ) const override;

    model::chip8::key getPressedKey() const override;

    void set( Qt::Key key );
    void unset( Qt::Key key );

private:
    model::chip8::key      m_key = model::chip8::key::none;
    std::array<bool, 0x10> m_keypad{};
};
