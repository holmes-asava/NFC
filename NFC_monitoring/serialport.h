#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>


class SerialPort : public QObject
{
    Q_OBJECT
public:
    SerialPort(QObject *parent = 0);

private slots:
    void readSerial();

private:
    QSerialPort *TRF7970Aevm;
    static const quint16 TRF7970Aevm_vendor_id = 4292;
    static const quint16 TRF7970Aevm_product_id = 60000;
    QByteArray serialData;
};

#endif // SERIALPORT_H
