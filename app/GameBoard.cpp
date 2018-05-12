#include "GameBoard.hpp"

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>

#include <algorithm>
#include <iostream>

GameBoard::GameBoard( model::VM vm, QWidget* parent )
: QWidget{ parent }
, m_vm{ vm }
{
}

void GameBoard::paintEvent( QPaintEvent* )
{
    m_vm.cycle();

    QPainter painter{ this };

    const QColor white{ 255, 255, 255, 255 };
    const QColor black{ 0, 0, 0, 255 };

    painter.fillRect(
        QRect{ QPoint{ 0, 0 },
               QSize{ model::chip8::display_width * m_quadSize, model::chip8::display_height * m_quadSize } },
        black );

    for ( int i = 0; i < model::chip8::display_size; i++ )
    {
        if ( m_vm.getCPU().buffer()[i] != 0 )
        {
            const int x = m_quadSize * ( i % model::chip8::display_width );
            const int y = m_quadSize * ( i / model::chip8::display_width );
            painter.fillRect( QRect{ QPoint{ x, y }, QSize{ m_quadSize, m_quadSize } }, white );
        }
    }
}
