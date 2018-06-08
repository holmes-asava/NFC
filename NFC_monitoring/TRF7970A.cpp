 #include "TRF7970A.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <string>
#include <QDebug>
#include <QMessageBox>


TRF7970A::TRF7970A(QWidget *parent) :
    QDialog(parent)
{   a=0;
    arduino = new QSerialPort(this);
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
    /*
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
    QString arduino_uno_port_name;
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

        for(int i=1;i<3; i++)
        {
            switch (i) {

            case 1: sendData = "010C00030410003101000000";
                break;
            case 2: sendData = "010C00030410002101020000";
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

    if(serialData.data()[0]==0x5b)
    {
        char *text=new char[18];
         for(int i=1;i<18;i++)
        {
            text[i-1]=serialData.data()[i];
        }
        qDebug() <<text ;
        displaytext->graph(0)->addData(a,a+1);
        displaytext->xAxis->setRange(a, 100, Qt::AlignRight);
        displaytext->replot();
        a=a+1;


    }
}

void TRF7970A::plotGraph()
{
    sendData = "010B000304180220020000";
    writeSerial();
    QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
}

