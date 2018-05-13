#include "MainWindow.hpp"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow( QWidget* parent )
: QMainWindow( parent )
, ui( new Ui::MainWindow )
, m_vm{ m_ioDevice }
, gameBoard{ m_vm.getCPU().buffer().data(), model::chip8::display_width, model::chip8::display_height }
, timer{ this }
{
    // m_vm.loadRom( "/Users/diogo.benvenutti/draft/roms/IBM Logo.ch8" );
    m_vm.loadRom( "/Users/diogo.benvenutti/draft/roms/Keypad Test [Hap, 2006].ch8" );

    ui->setupUi( this );
    setWindowTitle( "core8" );

    gameBoard.setFixedWidth( 500 );
    gameBoard.setFixedHeight( 250 );
    ui->gameLayout->addWidget( &gameBoard );

    connect( &timer, SIGNAL( timeout() ), this, SLOT( cycle() ) );

    timer.start( 1 );
}

void MainWindow::cycle()
{
    m_vm.cycle();

    if ( m_vm.getCPU().m_drawFlag )
    {
        gameBoard.update();
        m_vm.getCPU().m_drawFlag = false;
    }
}

MainWindow::~MainWindow()
{
    timer.stop();
    delete ui;
}
