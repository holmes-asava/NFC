#include "ndfwifget.h"
#include <QtWidgets>
NdfWifget::NdfWifget(QWidget *parent)
    : QTabWidget(parent)
{

    setTab = new SetTab(this);
    connect(setTab, &SetTab::sendDetails,
        this, &AddressWidget::addEntry);

    addTab(newAddressTab, "Address Book");

    setupTabs();
}
