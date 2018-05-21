#pragma once

#include "IoDeviceImpl.hpp"
#include "ScreenWidget.hpp"

#include <model/VM.hpp>

#include <QMainWindow>
#include <QTimer>

namespace Ui
{
class MainWindow;
}

class ScreenWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget* parent = nullptr );
    ~MainWindow();

public slots:
    void cycle();
    void selectRomFile();

private:
    void keyPressEvent( QKeyEvent* event ) override;
    void keyReleaseEvent( QKeyEvent* event ) override;

    Ui::MainWindow* ui;

    IoDeviceImpl m_ioDevice;
    model::VM    m_vm;
    bool         m_isRunning = false;

    ScreenWidget m_screen;
    QTimer       m_timer;
};
