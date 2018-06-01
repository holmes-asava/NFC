#include "mainwindow.h"



#include <QAction>
#include <QFileDialog>
#include <QMenuBar>
MainWindow::MainWindow()
{
    nfcWidget = new NFCWidget;

    setWindowTitle(tr("NFC Monitoring"));
}

