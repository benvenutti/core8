#include "ScreenWidget.hpp"

#include <QImage>
#include <QPainter>
#include <QRect>

#include <cassert>

ScreenWidget::ScreenWidget( const std::uint32_t* buffer, int w, int h )
: QWidget{ nullptr }
, m_buffer{ reinterpret_cast<const uchar*>( buffer ) }
, m_screenWidth{ w }
, m_screenHeight{ h }
{
    assert( m_buffer != nullptr );
}

void ScreenWidget::paintEvent( QPaintEvent* )
{
    QPainter{ this }.drawImage( QRect{ 0, 0, width(), height() },
                                QImage{ m_buffer, m_screenWidth, m_screenHeight, QImage::Format_ARGB32 },
                                QRect{ 0, 0, m_screenWidth, m_screenHeight } );
}
