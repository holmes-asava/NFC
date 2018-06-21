 #include "TRF7970A.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <string>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

TRF7970A::TRF7970A(QWidget *parent) :
    QDialog(parent)
{   state=0;
    a=0;
    arduino = new QSerialPort(this);
    sendData="";
    displaytext =new QCustomPlot    ;
    displaytext ->addGraph();
    displaytext->graph(0)->setPen(QPen(QColor(40, 110, 255)));//set color
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%s");
    displaytext->xAxis->setTicker(timeTicker);
    displaytext->axisRect()->setupFullAxesBox();
    displaytext->yAxis->setRange(20,38);
    displaytext->plotLayout()->insertRow(0);
    displaytext->plotLayout()->addElement(0, 0, new QCPTextElement(displaytext, "temperature", QFont("Times",12,QFont::Light)));
        // give the axes some labels:
    displaytext ->xAxis->setLabel("time");
    displaytext ->yAxis->setLabel("temp");
        // set axes ranges, so we see all data:
    connect( displaytext ->xAxis, SIGNAL(rangeChanged(QCPRange)), displaytext->xAxis2, SLOT(setRange(QCPRange)));
    connect( displaytext ->yAxis, SIGNAL(rangeChanged(QCPRange)), displaytext->yAxis2, SLOT(setRange(QCPRange)));


    displaytext2     =new QCustomPlot    ;
    displaytext2 ->addGraph();
    displaytext2->graph(0)->setPen(QPen(QColor(40, 110, 255)));//set color
    displaytext2->xAxis->setTicker(timeTicker);
    displaytext2->axisRect()->setupFullAxesBox();
    displaytext2->yAxis->setRange(28,38);
    displaytext2->plotLayout()->insertRow(0);
    displaytext2->plotLayout()->addElement(0, 0, new QCPTextElement(displaytext2, "sensor", QFont("Times", 12, QFont::Light)));
        // give the axes some labels:
    displaytext2 ->xAxis->setLabel("time");
    displaytext2 ->yAxis->setLabel("temp");
        // set axes ranges, so we see all data:
    connect( displaytext2 ->xAxis, SIGNAL(rangeChanged(QCPRange)), displaytext2->xAxis2, SLOT(setRange(QCPRange)));
    connect( displaytext2 ->yAxis, SIGNAL(rangeChanged(QCPRange)), displaytext2->yAxis2, SLOT(setRange(QCPRange)));

    /*
     *
     *  Testing code, prints the description, vendor id, and product id of all ports.
     *  Used it to determine the values for the arduino uno.
     *
     *
    qDebug() << "Number of ports: " << QSerialPortInfo::availablePorts().length() << "\n";
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "Description: " << serialPortInfo.description() << "\n";
        qDebug() << "Has vendor id?: " << serialPortInfo.hasVendorIdentifier() << "\n";
        qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n";
        qDebug() << "Has product id?: " << serialPortInfo.hasProductIdentifier() << "\n";
        qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "\n";
    }
    */
}

TRF7970A::~TRF7970A()
{
    if(arduino->isOpen()){
        arduino->close(); //    Close the serial port if it's open.
    }
}

bool TRF7970A::configuring()
{
    bool arduino_is_available = false;

    //
    //  For each available serial port
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        //  check if the serialport has both a product identifier and a vendor identifier
        if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
            //  check if the product ID and the vendor ID match those of the arduino uno
            if((serialPortInfo.productIdentifier() == arduino_uno_product_id)
                    && (serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id)){
                arduino_is_available = true; //    arduino uno is available on this port
                arduino_uno_port_name = serialPortInfo.portName();
            }
        }
    }
    qDebug()<<arduino_is_available;

    /*
     *  Open and configure the arduino port if available
     */
    if(arduino_is_available){
        qDebug() << "Found the arduino port...\n";
        arduino->setPortName(arduino_uno_port_name);
        arduino->open(QSerialPort::ReadWrite);
        arduino->setBaudRate(QSerialPort::Baud115200);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);

        for(int i=1;i<2; i++)
        {
            switch (i)
            {   //write register default
            case 1: sendData = "010C00030410002101020000";
                    break;

            }
            writeSerial();
              QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
        }
        return true;
    }
    else{
            qDebug() << "Couldn't find the correct port for the arduino.\n";
            QMessageBox::information(this, "Serial Port Error", "Couldn't open serial port to arduino.");

            return false;
        }
}

void TRF7970A::writeSerial()
{
    QByteArray Sendbyte;
    Sendbyte.append(sendData);
    //qDebug() << Sendbyte;
    arduino->write(Sendbyte);
}

void TRF7970A::readSerial()
{
    serialData = arduino->readAll();
    int numsize=serialData.size();
    if(numsize>0)
    {

    if((serialData.data()[0]==0x5b)&&(numsize>15))
            //&&serialData.data()[19]==0x5d)
    {   qDebug()<<serialData;
        int dec[8];
        for(int k=3;k<11;k++)
        {   if((serialData.data()[k]>=65)&&serialData.data()[k]<=70)
            {dec[k-3]=serialData.data()[k]-55;}
            else
            {
            dec[k-3]=serialData.data()[k]-48;
            }

        }


        float ref_value = (dec[2])*(16*16*16)+(dec[3])*(16*16)+(dec[0])*16+(dec[1]);

        float temp_value = (dec[6])*(16*16*16)+(dec[7])*(16*16)+(dec[4])*16+(dec[5]);
        qDebug()<<temp_value;
        qDebug()<<ref_value;
        /*if(dec[2]>=2)
        {
           ref_value=ref_value-(2*8192);
        }
        if(dec[6]>=2)
        {
           temp_value=temp_value-(2*8192);
        }
        */

        float temp= 298.15*4330/((298.15*(log(temp_value/ref_value))) + 4330.0) - 273.15;
        qDebug()<<temp;
        displaytext->graph(0)->addData(a,temp);
        displaytext->xAxis->setRange(a, 100,Qt::AlignRight);
        displaytext->replot();
        a=a+1;
        QString str = QString::number(temp);
        saveData.append(str);
        saveData.append(" \n ");
        //qDebug()<<saveData;


    }
    }
}

void TRF7970A::plotGraph()
{
    if(state!=0)
    {
        sendData = "010C00030418022309000000";
    writeSerial();
    QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
    state=state+1;
    }
    else
    {//write block0
    sendData = "01130003041802210001000300010100400000";
    writeSerial();
    QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
    state=state+1;
    }
    state=state%2;
}

void TRF7970A::save()
{
    QString fileName = QFileDialog::getSaveFileName(this,
           tr("Save Data"), "",
           tr("text (*.txt);;All Files (*)"));

    if (fileName.isEmpty())
           return;
       else {
           QFile file(fileName);
           if (!file.open(QIODevice::WriteOnly)) {
               QMessageBox::information(this, tr("Unable to open file"),
                   file.errorString());
               return;
           }

           QDataStream out(&file);
           out.setVersion(QDataStream::Qt_4_5);
           out << saveData;
           QMessageBox msgBox;
           msgBox.setText("Save Complete");
           msgBox.exec();
       }
}



