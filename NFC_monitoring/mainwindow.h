#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QWidget>
#include<QPushButton>
#include<QHBoxLayout>
#include<QGridLayout>
#include<QLabel>
#include<QLineEdit>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
private slots:
    void handlelCon();

private:
    QLabel *port;
    QWidget *window;
    QLabel *status;

    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;


    QHBoxLayout *portlayout ;
    QHBoxLayout *statuslayout ;
    QHBoxLayout *buttonlayout ;

    QGridLayout *settinglayout ;

};

#endif // MAINWINDOW_H
