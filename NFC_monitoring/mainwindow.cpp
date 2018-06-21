#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)

{       timer = new QTimer(this);
        device = new TRF7970A;

        NFCstart=false;
        i=0;
        device  = new TRF7970A;
        window  = new QWidget;
        port    = new QLabel("Port: none");
        status  = new QLabel("Status: Disconnect");
        button1 = new QPushButton("Connect",this);
        button2 = new QPushButton("Start");
        button3 = new QPushButton("Stop");
        saveButton = new QPushButton("Save");
        button2->setEnabled(false);
        button3->setEnabled(false);
        connect(button1, SIGNAL (released()), this, SLOT (handlelCon()));
        connect(button2, SIGNAL (released()), this, SLOT (handlelstart()));
        connect(button3, SIGNAL (released()), this, SLOT (handlelstop()));
        connect(saveButton, SIGNAL (released()), this, SLOT (handlelsave()));
        portlayout  = new QHBoxLayout ;
        statuslayout= new QHBoxLayout ;
        buttonlayout= new QHBoxLayout ;


        portlayout->addWidget(port);
        statuslayout->addWidget(status);
        buttonlayout->addWidget(button1);
        buttonlayout->addWidget(button2);
        buttonlayout->addWidget(button3);
        buttonlayout->addWidget(saveButton);
        settinglayout=new QGridLayout ;
        settinglayout->addLayout(portlayout,0,0);
        settinglayout->addLayout(statuslayout,1,0);
        settinglayout->addLayout(buttonlayout,2,0);
        settingGP= new QGroupBox("setting");
        settingGP->setLayout(settinglayout);
        settingGP->setFixedSize(300,150);



            // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
         // Interval 0 means


        displaylayout   =new QGridLayout ;
        displayGP       =new QGroupBox("monitor") ;
        displaylayout->addWidget(device->displaytext,0,0);
        displaylayout->addWidget(device->displaytext2,0,1);
        displayGP->setLayout(displaylayout);

      //  displayGP->setSizePolicy(2000,2000);
        mainlayout      =new QGridLayout ;
        mainlayout->addWidget(settingGP,0,0);
        mainlayout->addWidget(displayGP,1,0,1,2);
        window->setLayout(mainlayout);
        window->setMinimumSize(800,500);
        window->show();







}

void MainWindow::handlelCon()
{

   if(device->configuring())
   {
   button1->setText("Conected");
   button2->setEnabled(true);
   port->setText("Port: "+ device->arduino_uno_port_name);
   status->setText("Status: Connected");


   }
   else
   {

   }
}
void MainWindow::handlelstart()
{
      // change the text
      if(NFCstart==false)
      {
      button2->setText("Pause");
      button3->setEnabled(true);

      NFCstart=true;
      device->saveData.clear();
      timer->start(200);

      }
      else
      {
      button2->setText("Start");

      NFCstart=false;


      }



}
void MainWindow::handlelstop()
{
   button2->setText("Start");
   NFCstart=false;
   button3->setEnabled(false);
   button2->setEnabled(true);
   timer->stop();

   device->displaytext->removeGraph(0);
   device->displaytext->addGraph(0);
   device->displaytext->graph(0)->setPen(QPen(QColor(40, 110, 255)));
   device->a=0;


}
void MainWindow::handlelsave()
{
    device->save();
}

void MainWindow::update()
{
    if(NFCstart==true)
    {   device->plotGraph();

    }
    else
    {   device->displaytext->graph(0)->addData(device->a,0);
        device->a=device->a+1;
        qDebug()<<device->a;
    }
}




