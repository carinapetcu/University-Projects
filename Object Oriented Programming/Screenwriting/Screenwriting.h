#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Screenwriting.h"
#include "Service.h"
#include "TapesTableModel.h"
#include <qsortfilterproxymodel.h>

class Screenwriting : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    Screenwriting(Service& service, TapesTableModel* model, Writer writer, QWidget *parent = Q_NULLPTR);

private:
    Ui::ScreenwritingClass ui;
    Service& service;
    TapesTableModel* model;
    Writer writer;
    void update();
    void connectSignalsAndSlots();

    void addIdea();
    void reviseIdea();
};
