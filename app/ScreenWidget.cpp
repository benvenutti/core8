#include "ScreenWidget.hpp"

#include <model/VM.hpp>

#include <QImage>
#include <QPainter>
#include <QRect>

namespace detail
{
constexpr QRect source{ 0, 0, model::chip8::display_width, model::chip8::display_height };
}

ScreenWidget::ScreenWidget( const model::CPU::VideoBuffer& buffer )
: QWidget{ nullptr }
, m_buffer{ buffer }
{
}

void ScreenWidget::paintEvent( QPaintEvent* )
{
    QPainter{ this }.drawImage( QRect{ 0, 0, width(), height() },
                                QImage{ reinterpret_cast<const uchar*>( m_buffer.data() ),
                                        model::chip8::display_width,
                                        model::chip8::display_height,
                                        QImage::Format_RGB32 },
                                detail::source );
}
