#include "MainWindow.hpp"
#include "ui_mainwindow.h"

#include "GameBoard.hpp"

#include <QColorDialog>

MainWindow::MainWindow( QWidget* parent )
: QMainWindow( parent )
, ui( new Ui::MainWindow )
, m_vm{ m_ioDevice }
, gameBoard{ new GameBoard{ m_vm } }
, timer{ this }
{
    // m_vm.loadRom( "/Users/diogo.benvenutti/draft/roms/IBM Logo.ch8" );
    m_vm.loadRom( "/Users/diogo.benvenutti/draft/roms/Keypad Test [Hap, 2006].ch8" );

    ui->setupUi( this );
    setWindowTitle( "core8" );

    gameBoard->setFixedWidth( 600 );
    gameBoard->setFixedHeight( 300 );
    ui->gameLayout->addWidget( gameBoard );

    connect( &timer, SIGNAL( timeout() ), gameBoard, SLOT( update() ) );

    timer.start();
}

MainWindow::~MainWindow()
{
    timer.stop();
    delete ui;
}
