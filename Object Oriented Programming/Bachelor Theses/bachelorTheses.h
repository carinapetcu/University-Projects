#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_bachelorTheses.h"
#include "Service.h"
#include "Observer.h"
#include <string>
#include <vector>

class bachelorTheses : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    bachelorTheses(Service& service, std::string name, QWidget *parent = Q_NULLPTR);

private:
    Ui::bachelorThesesClass ui;
    Service& service;
    std::string name;

    void populateList();
    void update();
    void connectSingalsAndSlots();

    void addAsCoordinator();
    void editStudent();
    void filterList();
    int getSelectedIndex() const;
    void activateButton();
};
