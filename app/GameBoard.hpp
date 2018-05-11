#pragma once

#include <QColor>
#include <QWidget>

#include <cstddef>

class QPainter;

class GameBoard : public QWidget
{
    Q_OBJECT

public:
    explicit GameBoard( QWidget* parent = nullptr );

private:
    void paintEvent( QPaintEvent* event ) override;

    const std::size_t gridSize{ 60 };
    QColor            m_color;
};
