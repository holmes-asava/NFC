#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
        window  = new QWidget;
        port    = new QLabel("Port: none");
        status  = new QLabel("Status: Disconnect");
        button1 = new QPushButton("Connect",this);
        button2 = new QPushButton("Start");
        button3 = new QPushButton("Stop");
        connect(button1, SIGNAL (released()), this, SLOT (handlelCon()));
        portlayout  = new QHBoxLayout ;
        statuslayout= new QHBoxLayout ;
        buttonlayout= new QHBoxLayout ;


        portlayout->addWidget(port);
        statuslayout->addWidget(status);
        buttonlayout->addWidget(button1);
        buttonlayout->addWidget(button2);
        buttonlayout->addWidget(button3);
        settinglayout=new QGridLayout ;
        settinglayout->addLayout(portlayout,0,0);
        settinglayout->addLayout(statuslayout,1,0);
        settinglayout->addLayout(buttonlayout,2,0);

        window->setLayout(settinglayout);
        window->show();




}

void MainWindow::handlelCon()
{
   // change the text
   button1->setText("Example");
   // resize button


}



