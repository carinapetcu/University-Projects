#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_IssueTracker.h"
#include "Service.h"
#include "Observer.h"

class IssueTracker : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    IssueTracker(Service& service, User user, QWidget *parent = Q_NULLPTR);

private:
    Ui::IssueTrackerClass ui;
    Service& service;
    User user;

    void populateList();
    void connectSignalsAndSlots();
    void update() override;

    void addIssue();
    void removeIssue();
    void updateIssue();
    void activateOrDeactivateResolve();

    int getSelectedIndex() const;
};
