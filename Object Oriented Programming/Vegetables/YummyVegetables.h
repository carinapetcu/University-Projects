#pragma once
#include "Service.h"
#include "Domain.h"

#include <QtWidgets/QMainWindow>
#include "ui_YummyVegetables.h"

class YummyVegetables : public QMainWindow
{
    Q_OBJECT

public:
    YummyVegetables(Service& service, QWidget *parent = Q_NULLPTR);

private:
    Ui::YummyVegetablesClass ui;
    Service& service;
    void populateList();
    void connectSignalsAndSlots();
    std::string getSelectedItem() const;

    void vegetableList();
    void getVegetable();
};
