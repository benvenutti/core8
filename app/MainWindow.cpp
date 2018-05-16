#include "MainWindow.hpp"
#include "ui_mainwindow.h"

#include <QKeyEvent>

#include <QDebug>

MainWindow::MainWindow( QWidget* parent )
: QMainWindow( parent )
, ui( new Ui::MainWindow )
, m_vm{ m_ioDevice }
, gameBoard{ m_vm.getCPU().buffer().data(), model::chip8::display_width, model::chip8::display_height }
, timer{ this }
{
    // m_vm.loadRom( "/Users/diogo.benvenutti/draft/roms/IBM Logo.ch8" );
    m_vm.loadRom( "/home/diogo/Downloads/Keypad Test [Hap, 2006].ch8" );

    ui->setupUi( this );
    setWindowTitle( "core8" );

    gameBoard.setFixedWidth( 500 );
    gameBoard.setFixedHeight( 250 );
    ui->gameLayout->addWidget( &gameBoard );

    connect( &timer, &QTimer::timeout, this, &MainWindow::cycle );

    timer.start( 1 );
}

MainWindow::~MainWindow()
{
    timer.stop();
    delete ui;
}

void MainWindow::cycle()
{
    m_vm.cycle();

    if ( m_vm.getCPU().drawFlag() )
    {
        gameBoard.update();
    }
}

void MainWindow::keyPressEvent( QKeyEvent* event )
{
    m_ioDevice.set( event->key(), true );
}

void MainWindow::keyReleaseEvent( QKeyEvent* event )
{
    m_ioDevice.set( event->key(), false );
}
