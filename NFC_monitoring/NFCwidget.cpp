#include "nfcwidget.h"
#include <QtWidgets>
NFCWidget::NFCWidget()
{


    descriptionLabel = new QLabel(tr("There are currently no contacts in your address book. "
                                      "\nClick Add to add new contacts."));

    addButton = new QPushButton(tr("Add"));

    connect(addButton, &QAbstractButton::clicked, this, &NewAddressTab::addEntry);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(descriptionLabel);
    mainLayout->addWidget(addButton, 0, Qt::AlignCenter);

    setLayout(mainLayout);
}
