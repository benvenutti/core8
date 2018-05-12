#pragma once

#include <model/Chip8.hpp>
#include <model/VM.hpp>

#include <QColor>
#include <QPainter>
#include <QWidget>

#include <array>
#include <cstddef>

class QPainter;

class GameBoard : public QWidget
{
    Q_OBJECT

public:
    explicit GameBoard( model::VM vm, QWidget* parent = nullptr );

private:
    void paintEvent( QPaintEvent* event ) override;

    const int m_quadSize{ 1 };
    model::VM m_vm;
};
