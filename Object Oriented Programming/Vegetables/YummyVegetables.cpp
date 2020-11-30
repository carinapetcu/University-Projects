#include "YummyVegetables.h"

YummyVegetables::YummyVegetables(Service& service, QWidget *parent)
    : service(service), QMainWindow(parent)
{
    ui.setupUi(this);
    this->populateList();
    this->connectSignalsAndSlots();
}

void YummyVegetables::populateList()
{
    this->ui.familyListWidget->clear();
    this->ui.familyListWidget->setSortingEnabled(true);
    std::vector<Domain> allEntities = this->service.getAllElements();
    std::vector<std::string> allFamilies;
    for (auto entity : allEntities)
    {
        if (std::find(allFamilies.begin(), allFamilies.end(), entity.getFamily()) == allFamilies.end())
            allFamilies.push_back(entity.getFamily());
    }
    for (auto family : allFamilies)
    {
        this->ui.familyListWidget->addItem(QString::fromStdString(family));
    }
    this->ui.familyListWidget->sortItems();
}

void YummyVegetables::connectSignalsAndSlots()
{
    QObject::connect(this->ui.familyListWidget, &QListWidget::itemSelectionChanged, this, &YummyVegetables::vegetableList);
    QObject::connect(this->ui.searchPushButton, &QPushButton::clicked, this, &YummyVegetables::getVegetable);
}

std::string YummyVegetables::getSelectedItem() const
{
    return this->ui.familyListWidget->currentItem()->text().toStdString();
}

void YummyVegetables::vegetableList()
{
    std::string family = this->getSelectedItem();
    std::vector<Domain> allEntities = this->service.getAllElements();
    this->ui.vegetablesListWidget->clear();
    for (auto entity : allEntities)
    {
        if (entity.getFamily() == family)
        {
            std::string partsToEat{ "" };
            partsToEat += entity.getName() + ":";
            partsToEat += entity.getConsumed()[0];
            for (int index = 1; index < entity.getConsumed().size(); index++)
            {
                partsToEat += ",";
                partsToEat += entity.getConsumed()[index];
            }
            this->ui.vegetablesListWidget->addItem(QString::fromStdString(partsToEat));
        }
    }
}

void YummyVegetables::getVegetable()
{
    std::string name =this->ui.vegetableLineEdit->text().toStdString();
    std::vector<Domain> allEntities = this->service.getAllElements();
    for (auto entity : allEntities)
    {
        if (entity.getName() == name)
        {
            std::string partsToEat{ "" };
            partsToEat += entity.getConsumed()[0];
            for (int index = 1; index < entity.getConsumed().size(); index++)
            {
                partsToEat += ",";
                partsToEat += entity.getConsumed()[index];
            }
            this->ui.consumedLineEdit->setText(QString::fromStdString(partsToEat));
        }
    }
}
