 #ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QByteArray>

class TRF7970A : public QDialog
{
    Q_OBJECT

public:
    explicit TRF7970A(QWidget *parent = 0);
    ~TRF7970A();
    bool configuring();
    void writeSerial();
    void plotGraph();

private slots:
    void readSerial();

private:
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 4292;
    static const quint16 arduino_uno_product_id = 60000;
    QByteArray serialData;
    QString sendData;

};

#endif // DIALOG_H
