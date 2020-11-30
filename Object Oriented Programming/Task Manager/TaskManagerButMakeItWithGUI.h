#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TaskManagerButMakeItWithGUI.h"
#include "Service.h"
#include "Tape.h"

class TaskManagerButMakeItWithGUI : public QMainWindow
{
    Q_OBJECT

public:
    TaskManagerButMakeItWithGUI(Service& service, QWidget *parent = Q_NULLPTR);

private:
    Ui::TaskManagerButMakeItWithGUIClass ui;
    Service& service;
    void populateList();
    void connectSignalsAndSlots();

    void getDurationByPriority();
};
