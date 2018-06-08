 #include "TRF7970A.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <string>
#include <QDebug>
#include <QMessageBox>


TRF7970A::TRF7970A(QWidget *parent) :
    QDialog(parent)
{
    arduino = new QSerialPort(this);

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

        for(int i=1; i<=3; i++)
        {
            switch (i) {
            //case 0: sendData = "0108000304FF0000";
               // break;
            case 1: sendData = "010C00030410003101000000";
                break;
            case 2: sendData = "010C00030410002101020000";
                break;
            //case 3: sendData = "0109000304F0000000";
               // break;
            //case 4: sendData = "0109000304F1FF0000";
                //break;
            //case 3: sendData = "010B000304180220010000";
              //  break;
            //case 2: sendData = "01120003041820021052FE01000007E00000";
              //  break; //quite
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
    qDebug() <<serialData ;
}

void TRF7970A::plotGraph()
{
    sendData = "010B000304180220010000";
    writeSerial();
    QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
}

