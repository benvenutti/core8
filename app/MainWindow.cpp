#include "MainWindow.hpp"
#include "ui_mainwindow.h"

#include <QColorDialog>

MainWindow::MainWindow( QWidget* parent )
: QMainWindow( parent )
, ui( new Ui::MainWindow )
{
    ui->setupUi( this );
}

MainWindow::~MainWindow()
{
    delete ui;
}
