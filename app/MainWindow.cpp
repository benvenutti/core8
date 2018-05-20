#include "MainWindow.hpp"
#include "ui_mainwindow.h"

#include <QKeyEvent>

#include <QDebug>

MainWindow::MainWindow( QWidget* parent )
: QMainWindow( parent )
, ui( new Ui::MainWindow )
, m_vm{ m_ioDevice }
, m_screen{ m_vm.getCPU().buffer().data(), model::chip8::display_width, model::chip8::display_height }
, m_timer{ this }
{
    // m_vm.loadRom( "/Users/diogo.benvenutti/draft/roms/IBM Logo.ch8" );
    m_vm.loadRom( "/home/diogo/Downloads/Keypad Test [Hap, 2006].ch8" );

    ui->setupUi( this );
    setWindowTitle( "core8" );

    m_screen.setFixedWidth( 500 );
    m_screen.setFixedHeight( 250 );
    ui->gameLayout->addWidget( &m_screen );

    connect( &m_timer, &QTimer::timeout, this, &MainWindow::cycle );

    m_timer.start( 1 );
}

MainWindow::~MainWindow()
{
    m_timer.stop();
    delete ui;
}

void MainWindow::cycle()
{
    m_vm.cycle();

    if ( m_vm.getCPU().drawFlag() )
    {
        m_screen.update();
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
