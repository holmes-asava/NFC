#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "TRF7970A.h"
#include <QMainWindow>
#include<QWidget>
#include<QPushButton>
#include<QHBoxLayout>
#include<QGridLayout>
#include<QLabel>
#include<QLineEdit>
#include<QGroupBox>
#include<QTextEdit>
#include<QTimer>
#include<qcustomplot.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QTimer *timer;
    explicit MainWindow(QWidget *parent = 0);
private slots:
    void handlelCon();
    void handlelstop();
    void update();
private:
    QLabel *port;
    QWidget *window;
    QLabel *status;

    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;

    QCustomPlot *displaytext;

    QHBoxLayout *portlayout ;
    QHBoxLayout *statuslayout ;
    QHBoxLayout *buttonlayout ;

    QGridLayout *settinglayout ;
    QGridLayout *displaylayout ;
    QGridLayout *mainlayout;
    TRF7970A *device;

    QGroupBox *settingGP;
    QGroupBox *displayGP;
    int i;
    int NFCdata;
    bool NFCstart;

};

#endif // MAINWINDOW_H
