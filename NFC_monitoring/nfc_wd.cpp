#include "nfc_wd.h"
#include <QtWidgets>
nfc_wd::nfc_wd(QWidget *parent)
{ Q_UNUSED(parent);

    descriptionLabel = new QLabel("There are currently no contacts in your address book. "
                                      "\nClick Add to add new contacts.");

    addButton = new QPushButton(tr("Add"));


    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(descriptionLabel);
    mainLayout->addWidget(addButton, 0, Qt::AlignCenter);

    setLayout(mainLayout);

}
