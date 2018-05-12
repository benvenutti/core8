#pragma once

#include <model/CPU.hpp>

#include <QWidget>

class ScreenWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenWidget( const model::CPU::VideoBuffer& buffer );

private:
    void paintEvent( QPaintEvent* event ) override;

    const int                      m_quadSize{ 5 };
    const model::CPU::VideoBuffer& m_buffer;
};
