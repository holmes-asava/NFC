#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)

{       timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        timer->start(1000);
        NFCstart=false;
        i=0;
        window  = new QWidget;
        port    = new QLabel("Port: none");
        status  = new QLabel("Status: Disconnect");
        button1 = new QPushButton("Connect",this);
        button2 = new QPushButton("Start");
        button3 = new QPushButton("Stop");
        button2->setEnabled(false);
        button3->setEnabled(false);
        connect(button1, SIGNAL (released()), this, SLOT (handlelCon()));
        connect(button3, SIGNAL (released()), this, SLOT (handlelstop()));
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
        settingGP= new QGroupBox("setting");
        settingGP->setLayout(settinglayout);
        settingGP->show();

        displaytext     =new QTextEdit;
        displaylayout   =new QGridLayout ;
        displayGP       =new QGroupBox("monitor") ;
        displaylayout->addWidget(displaytext);
        displayGP->setLayout(displaylayout);

        mainlayout      =new QGridLayout ;
        mainlayout->addWidget(settingGP,0,0);
        mainlayout->addWidget(displayGP,1,0);
        window->setLayout(mainlayout);
        window->show();






}

void MainWindow::handlelCon()
{
   // change the text
   if(button1->text()=="Connect")
   {
   button1->setText("Example");
   button3->setEnabled(true);

   NFCstart=true;
   }
   i=0;


}
void MainWindow::handlelstop()
{
   // change the text
   NFCstart=false;
   button3->setEnabled(false);


}

void MainWindow::update()
{
    if(NFCstart==true)
    {
          NFCdata=i;
          button2->setText(QString(NFCdata+48));
          i=i+1;


    }
}




