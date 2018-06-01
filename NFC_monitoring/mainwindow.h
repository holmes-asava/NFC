#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "nfcwidget.h"
#include <QMainWindow>



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   MainWindow();
private:


    NFCWidget *nfcWidget;



};

#endif // MAINWINDOW_H
