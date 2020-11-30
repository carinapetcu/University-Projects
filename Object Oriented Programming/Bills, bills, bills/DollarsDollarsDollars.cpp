#include "DollarsDollarsDollars.h"

DollarsDollarsDollars::DollarsDollarsDollars(Service& service, QWidget *parent)
    : service(service), QMainWindow(parent)
{
    ui.setupUi(this);
    this->populateList();
    this->connectSignalsAndSlots();
}

void DollarsDollarsDollars::populateList()
{
    this->ui.billListWidget->clear();
    std::vector<Domain> allEntities = this->service.getAllElements();
    for (auto entity : allEntities)
    {
        this->ui.billListWidget->addItem(QString::fromStdString(entity.getCompanyName() + ", " + std::to_string(entity.getSum())));
    }
}

void DollarsDollarsDollars::connectSignalsAndSlots()
{
    QObject::connect(this->ui.sortPushButton, &QPushButton::clicked, this, &DollarsDollarsDollars::sortList);
    QObject::connect(this->ui.calculateTotalPushButton, &QPushButton::clicked, this, &DollarsDollarsDollars::calculateTotal);
}

void DollarsDollarsDollars::sortList()
{
    this->ui.billListWidget->setSortingEnabled(true);
    this->populateList();
}

void DollarsDollarsDollars::calculateTotal()
{
    std::string companyName = this->ui.companyNameLineEdit->text().toStdString();
    float total = this->service.getUnpaidBillsTotal(companyName);
    this->ui.unpaidBillsLineEdit->clear();
    this->ui.unpaidBillsLineEdit->setText(QString::fromStdString(std::to_string(total)));
}
