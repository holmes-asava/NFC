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
        button2->setEnabled(false);
        button3->setEnabled(false);
        connect(button1, SIGNAL (released()), this, SLOT (handlelCon()));
        connect(button2, SIGNAL (released()), this, SLOT (handlelstart()));
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
        settingGP->setFixedSize(500,100);

        displaytext     =new QCustomPlot    ;
        displaytext ->addGraph();
        displaytext->graph(0)->setPen(QPen(QColor(40, 110, 255)));//set color
        QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
        timeTicker->setTimeFormat("%s");
        displaytext->xAxis->setTicker(timeTicker);
        displaytext->axisRect()->setupFullAxesBox();
        displaytext->yAxis->setRange(0,1000);
            // give the axes some labels:
        displaytext ->xAxis->setLabel("time");
        displaytext ->yAxis->setLabel("temp");
            // set axes ranges, so we see all data:
        connect( displaytext ->xAxis, SIGNAL(rangeChanged(QCPRange)), displaytext->xAxis2, SLOT(setRange(QCPRange)));
        connect( displaytext ->yAxis, SIGNAL(rangeChanged(QCPRange)), displaytext->yAxis2, SLOT(setRange(QCPRange)));

            // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        timer->start(10); // Interval 0 means


        displaylayout   =new QGridLayout ;
        displayGP       =new QGroupBox("monitor") ;
        displaylayout->addWidget(displaytext);
        displayGP->setLayout(displaylayout);

      //  displayGP->setSizePolicy(2000,2000);
        mainlayout      =new QGridLayout ;
        mainlayout->addWidget(settingGP,0,0);
        mainlayout->addWidget(displayGP,1,0);
        window->setLayout(mainlayout);
        window->setFixedSize(600,600);
        window->show();







}

void MainWindow::handlelCon()
{   /* Serialstate = Serialstart();
        if(Serialstare==1)
      */
   // change the text
   bool connect = device->configuring();
   if(connect)
   {
   button1->setText("Conected");
   button2->setEnabled(true);


   }
}
void MainWindow::handlelstart()
{
      // change the text
      if(NFCstart==false)
      {

      button3->setEnabled(true);
      button2->setEnabled(false);
      NFCstart=true;
      i=0;
      }



}
void MainWindow::handlelstop()
{
   // change the text
   NFCstart=false;
   button3->setEnabled(false);
   button2->setEnabled(true);

}

void MainWindow::update()
{
    if(NFCstart==true)
    {   //
        displaytext->graph(0)->addData(i,i+1);
        displaytext->xAxis->setRange(i, 100, Qt::AlignRight);
        displaytext->replot();

        if(i>800)
        {i=0;
        }
        else
        {
            i=i+1;
        }



    }
}




