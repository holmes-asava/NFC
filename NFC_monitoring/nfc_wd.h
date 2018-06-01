#ifndef NFC_WD_H
#define NFC_WD_H
#include <QWidget>
QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QVBoxLayout;
QT_END_NAMESPACE

class nfc_wd
{
public:
    nfc_wd(QWidget *parent = 0);
private:
    QLabel *descriptionLabel;
    QPushButton *addButton;
    QVBoxLayout *mainLayout;
};


#endif // NFC_WD_H
