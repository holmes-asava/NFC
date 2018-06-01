#ifndef NFCWIDGET_H
#define NFCWIDGET_H


#include <QWidget>
QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QVBoxLayout;
QT_END_NAMESPACE
class NFCWidget
{
public:
    NFCWidget();
private:
    QLabel *descriptionLabel;
    QPushButton *addButton;
    QVBoxLayout *mainLayout;
};

#endif // NFCWIDGET_H
