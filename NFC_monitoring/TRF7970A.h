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

private slots:
    void readSerial();
    void writeSerial();

private:
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 4292;
    static const quint16 arduino_uno_product_id = 60000;
    QByteArray serialData;

};

#endif // DIALOG_H
