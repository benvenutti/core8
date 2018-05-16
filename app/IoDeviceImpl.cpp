#include "IoDeviceImpl.hpp"

#include <QKeyEvent>

#include <algorithm>

namespace
{
const std::map<Qt::Key, int> keymap = { { Qt::Key_X, 0x0 }, { Qt::Key_1, 0x1 }, { Qt::Key_2, 0x2 }, { Qt::Key_3, 0x3 },
                                        { Qt::Key_Q, 0x4 }, { Qt::Key_W, 0x5 }, { Qt::Key_E, 0x6 }, { Qt::Key_A, 0x7 },
                                        { Qt::Key_S, 0x8 }, { Qt::Key_D, 0x9 }, { Qt::Key_Z, 0xa }, { Qt::Key_C, 0xb },
                                        { Qt::Key_4, 0xc }, { Qt::Key_R, 0xd }, { Qt::Key_F, 0xe }, { Qt::Key_V, 0xf } };
}

IoDeviceImpl::IoDeviceImpl()
{
}

void IoDeviceImpl::set( int key, bool pressed )
{
    auto it = keymap.find( static_cast<Qt::Key>( key ) );
    if ( it != keymap.end() )
    {
        m_keypad[it->second] = pressed;
    }
}

bool IoDeviceImpl::isKeyPressed( model::chip8::key key ) const
{
    return m_keypad[static_cast<int>( key )];
}

model::chip8::key IoDeviceImpl::getPressedKey() const
{
    auto it  = std::find( std::begin( m_keypad ), std::end( m_keypad ), std::true_type::value );
    auto key = std::distance( std::begin( m_keypad ), it );

    return static_cast<model::chip8::key>( key );
}