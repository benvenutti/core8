#include "GameBoard.hpp"

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>

#include <iostream>

GameBoard::GameBoard( QWidget* parent )
: QWidget{ parent }
, m_color{ 0, 0, 0, 255 }
{
}

void GameBoard::paintEvent( QPaintEvent* )
{
    // example of visual side effect
    static int cc = 0;
    m_color       = QColor{ ++cc, cc, cc, 255 };
    cc %= 254;

    QPainter painter{ this };
    painter.fillRect( QRect{ QPoint{ 0, 0 }, QSize{ 40, 40 } }, m_color );
}
