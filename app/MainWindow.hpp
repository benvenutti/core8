#pragma once

#include "IoDeviceImpl.hpp"

#include <model/VM.hpp>

#include <QMainWindow>
#include <QTimer>

namespace Ui
{
class MainWindow;
}

class GameBoard;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget* parent = nullptr );
    ~MainWindow();

private:
    Ui::MainWindow* ui;

    IoDeviceImpl m_ioDevice;
    model::VM    m_vm;

    GameBoard* gameBoard;
    QTimer     timer;
};
