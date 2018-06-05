#include "serialport.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

SerialPort::SerialPort(QObject *parent)
    : QObject(parent)
{
    TRF7970Aevm = new QSerialPort(this);

    /*
        *  Testing code, prints the description, vendor id, and product id of all ports.
        *
    qDebug() << "Number of ports: " << QSerialPortInfo::availablePorts().length() << "\n";
       foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
           qDebug() << "Description: " << serialPortInfo.description() << "\n";
           qDebug() << "Has vendor id?: " << serialPortInfo.hasVendorIdentifier() << "\n";
           qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n";
           qDebug() << "Has product id?: " << serialPortInfo.hasProductIdentifier() << "\n";
           qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "\n";

        }*/


    /*
         *   Identify the port the arduino uno is on.
         */
        bool TRF7970Aevm_is_available = false;
        QString TRF7970Aevm_port_name;
        //
        //  For each available serial port
        foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
            //  check if the serialport has both a product identifier and a vendor identifier
            if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
                //  check if the product ID and the vendor ID match those of the arduino uno
                if((serialPortInfo.productIdentifier() == TRF7970Aevm_product_id)
                        && (serialPortInfo.vendorIdentifier() == TRF7970Aevm_vendor_id)){
                    TRF7970Aevm_is_available = true; //    TRF7970Aevm is available on this port
                    TRF7970Aevm_port_name = serialPortInfo.portName();
                }
            }
        }
        qDebug() << "TRF7970Aevm status: " << TRF7970Aevm_is_available;

        if(TRF7970Aevm_is_available){
                qDebug() << "Found the arduino port...\n";
                TRF7970Aevm->setPortName(TRF7970Aevm_port_name);
                TRF7970Aevm->open(QSerialPort::ReadWrite);
                TRF7970Aevm->setBaudRate(QSerialPort::Baud115200);
                TRF7970Aevm->setDataBits(QSerialPort::Data8);
                TRF7970Aevm->setFlowControl(QSerialPort::NoFlowControl);
                TRF7970Aevm->setParity(QSerialPort::NoParity);
                TRF7970Aevm->setStopBits(QSerialPort::OneStop);

                QString test = "010B000304142401000000";
                bool ok;
                int n = test.size();
                QByteArray Sendbyte;

                for (int i=0; i<=n/2-1; i++){
                    QString a = test.mid(i*2,2);
                    qint8 b = a.toInt(&ok,16);
                    Sendbyte.append(b);
                }

                //qDebug() << Sendbyte;
                TRF7970Aevm->write(Sendbyte);
                while(1) {serialData = TRF7970Aevm->readAll();
                qDebug() << serialData;}
                qDebug() << Sendbyte;
                //QObject::connect(TRF7970Aevm, SIGNAL(readyRead()), this, SLOT(readSerial()));
            }else{
                qDebug() << "Couldn't find the correct port for the arduino.\n";
                //QMessageBox::information(this, "Serial Port Error", "Couldn't open serial port to arduino.");
            }
}

void SerialPort::readSerial()
{
    serialData = TRF7970Aevm->readAll();
    qDebug() << serialData;
}




