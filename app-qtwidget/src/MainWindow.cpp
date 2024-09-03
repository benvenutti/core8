#include "MainWindow.hpp"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QKeyEvent>
#include <QStandardPaths>

MainWindow::MainWindow( QWidget* parent )
: QMainWindow( parent )
, ui( new Ui::MainWindow )
, m_vm{ m_ioDevice }
, m_screen{ m_vm.getCPU().buffer().data(), model::chip8::display_width, model::chip8::display_height }
, m_timer{ this }
{
    ui->setupUi( this );
    setWindowTitle( "core8" );

    ui->screenLayout->addWidget( &m_screen );

    connect( &m_timer, &QTimer::timeout, this, &MainWindow::cycle );
    connect( ui->actionOpen_ROM, &QAction::triggered, this, &MainWindow::selectRomFile );

    int a = 10;

    m_timer.start( 1 );
}

MainWindow::~MainWindow()
{
    m_timer.stop();
    delete ui;
}

void MainWindow::cycle()
{
    if ( m_isRunning )
    {
        m_vm.cycle();

        if ( m_vm.getCPU().drawFlag() )
        {
            m_screen.update();
        }
    }
}

void MainWindow::selectRomFile()
{
    QFileDialog dlg{ this };
    dlg.setFileMode( QFileDialog::ExistingFile );
    dlg.setNameFilter( tr( "Chip8 files (*.ch8);;All files (*)" ) );
    dlg.setDirectory( QStandardPaths::standardLocations( QStandardPaths::HomeLocation ).front() );
    dlg.setViewMode( QFileDialog::List );

    if ( dlg.exec() )
    {
        const auto filenames = dlg.selectedFiles();
        m_isRunning          = !filenames.empty() && m_vm.loadRom( filenames.first().toStdString() );
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
