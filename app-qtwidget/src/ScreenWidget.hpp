#pragma once

#include <cstdint>

#include <QWidget>

class ScreenWidget : public QWidget
{
    Q_OBJECT

public:
    ScreenWidget( const std::uint32_t* buffer, int w, int h );

private:
    void paintEvent( QPaintEvent* event ) override;

    const uchar* m_buffer;
    const int    m_screenWidth;
    const int    m_screenHeight;
};
