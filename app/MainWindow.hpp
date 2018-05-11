#pragma once

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
    GameBoard*      gameBoard;
    QTimer          timer;
};
