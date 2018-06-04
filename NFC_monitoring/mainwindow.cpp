#include "mainwindow.h"
#include "serialport.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    SerialPort(0);
}

MainWindow::~MainWindow()
{

}
