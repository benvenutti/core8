#include "IoDeviceImpl.hpp"


#include <algorithm>

namespace
{
const std::map<Qt::Key, model::chip8::key> keymap = {
    { Qt::Key_X, model::chip8::key::k0 }, { Qt::Key_1, model::chip8::key::k1 }, { Qt::Key_2, model::chip8::key::k2 },
    { Qt::Key_3, model::chip8::key::k3 }, { Qt::Key_Q, model::chip8::key::k4 }, { Qt::Key_W, model::chip8::key::k5 },
    { Qt::Key_E, model::chip8::key::k6 }, { Qt::Key_A, model::chip8::key::k7 }, { Qt::Key_S, model::chip8::key::k8 },
    { Qt::Key_D, model::chip8::key::k9 }, { Qt::Key_Z, model::chip8::key::ka }, { Qt::Key_C, model::chip8::key::kb },
    { Qt::Key_4, model::chip8::key::kc }, { Qt::Key_R, model::chip8::key::kd }, { Qt::Key_F, model::chip8::key::ke },
    { Qt::Key_V, model::chip8::key::kf }
};
}

IoDeviceImpl::IoDeviceImpl()
{
    m_keypad.fill( false );
}

void IoDeviceImpl::set( Qt::Key key )
{
    auto it = keymap.find( key );
    m_key   = it != keymap.end() ? it->second : model::chip8::key::none;
}

void IoDeviceImpl::unset( Qt::Key )
{
    m_key = model::chip8::key::none;
}

bool IoDeviceImpl::isKeyPressed( model::chip8::key key ) const
{
    return m_key == key;
}

model::chip8::key IoDeviceImpl::getPressedKey() const
{
    return m_key;
}
