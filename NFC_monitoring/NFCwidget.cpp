#include "nfcwidget.h"

#include <QItemSelection>
#include <QtWidgets>
NFCWidget::NFCWidget()
{


    descriptionLabel = new QLabel(tr("There are currently no contacts in your address book. "
                                      "\nClick Add to add new contacts."));



    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(descriptionLabel);
    mainLayout->addWidget(addButton, 0, Qt::AlignCenter);

    setLayout(mainLayout);
}
