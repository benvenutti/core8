#include "GameBoard.hpp"

#include <model/Actions.hpp>

#include <boost/range/algorithm.hpp>

#include <QMouseEvent>
#include <QPainter>

#include <random>

namespace detail
{

auto randomBool() -> bool
{
    static std::random_device              rd;
    static std::mt19937                    eng{ rd() };
    static std::uniform_int_distribution<> distr{ 0, 2 };

    return static_cast<bool>( distr( eng ) );
}

} // namespace detail

GameBoard::GameBoard( QWidget* parent )
: QWidget{ parent }
, m_cellSystem{ gridSize, gridSize }
, m_color{ 0, 0, 0, 255 }
{
    clear();
}

auto GameBoard::clear() -> void
{
    model::iterate( m_cellSystem, [&]( const auto x, const auto y ) { m_cellSystem.set( x, y, false ); } );

    update();
}

auto GameBoard::generate() -> void
{
    model::iterate( m_cellSystem,
                    [&]( const auto x, const auto y ) { m_cellSystem.set( x, y, detail::randomBool() ); } );

    update();
}

auto GameBoard::cycle() -> void
{
    model::update( m_cellSystem );
    update();
}

auto GameBoard::paintEvent( QPaintEvent* ) -> void
{
    QPainter painter{ this };
    paintWorld( painter );
    paintGrid( painter );
}

auto GameBoard::mousePressEvent( QMouseEvent* e ) -> void
{
    double cellWidth  = (double) width() / gridSize;
    double cellHeight = (double) height() / gridSize;
    int    k          = floor( e->y() / cellHeight );
    int    j          = floor( e->x() / cellWidth );

    m_cellSystem.set( k, j, true );
    update();
}

auto GameBoard::mouseMoveEvent( QMouseEvent* e ) -> void
{
    double cellWidth  = (double) width() / gridSize;
    double cellHeight = (double) height() / gridSize;
    int    k          = floor( e->y() / cellHeight );
    int    j          = floor( e->x() / cellWidth );

    m_cellSystem.set( k, j, true );
    update();
}

auto GameBoard::paintWorld( QPainter& p ) -> void
{
    const auto cellWidth  = width() / gridSize;
    const auto cellHeight = height() / gridSize;
    for ( int k = 0; k < gridSize; k++ )
    {
        for ( int j = 0; j < gridSize; j++ )
        {
            if ( m_cellSystem.at( k, j ).isAlive() )
            {
                const auto  left = ( cellWidth * j );
                const auto  top  = ( cellHeight * k );
                const QRect r( QPoint( left, top ), QSize( cellWidth, cellWidth ) );

                p.fillRect( r, m_color );
            }
        }
    }
}

auto GameBoard::paintGrid( QPainter& painter ) -> void
{
    const auto cellWidth = width() / gridSize;
    for ( auto i = 0; i < width(); i += cellWidth )
        painter.drawLine( i, 0, i, height() );

    const auto cellHeight = height() / gridSize;
    for ( auto i = 0; i < height(); i += cellHeight )
        painter.drawLine( 0, i, width(), i );

    painter.drawRect( QRect{ 0, 0, width() - 1, height() - 1 } );
}
