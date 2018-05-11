#include "MainWindow.hpp"
#include "ui_mainwindow.h"

#include "GameBoard.hpp"

#include <QColorDialog>

MainWindow::MainWindow( QWidget* parent )
: QMainWindow( parent )
, ui( new Ui::MainWindow )
, gameBoard{ new GameBoard }
, timer{ this }
{
    ui->setupUi( this );

    gameBoard->setFixedWidth( 300 );
    gameBoard->setFixedHeight( 300 );
    ui->gameLayout->addWidget( gameBoard );

    connect( &timer, SIGNAL( timeout() ), gameBoard, SLOT( update() ) );

    timer.start( 15 );
}

MainWindow::~MainWindow()
{
    timer.stop();
    delete ui;
}
