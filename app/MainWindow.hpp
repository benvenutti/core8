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

private:
    Ui::MainWindow* ui;

    IoDeviceImpl m_ioDevice;
    model::VM    m_vm;

    ScreenWidget gameBoard;
    QTimer       timer;
};
