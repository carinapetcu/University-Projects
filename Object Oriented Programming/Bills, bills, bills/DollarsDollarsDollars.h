#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DollarsDollarsDollars.h"
#include "Service.h"

class DollarsDollarsDollars : public QMainWindow
{
    Q_OBJECT

public:
    DollarsDollarsDollars(Service& service, QWidget *parent = Q_NULLPTR);

private:
    Ui::DollarsDollarsDollarsClass ui;
    Service& service;
    void populateList();
    void connectSignalsAndSlots();

    void sortList();
    void calculateTotal();
};
