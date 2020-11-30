#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Exam.h"
#include "Service.h"
#include <string>
#include "TableModel.h"

class Exam : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    Exam(Service& service, Astronomer astronomer, TableModel* model, QWidget *parent = Q_NULLPTR);

private:
    Ui::ExamClass ui;
    Service& service;
    Astronomer astronomer;
    TableModel* model;

    void view();
    void connectSignalsAndSlots();
    void update();

    void add();
    void showConstellation();
    void seeFiltered();
};
