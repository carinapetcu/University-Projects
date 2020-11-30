#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QuestionAndAnswerSite.h"
#include "Domain.h"
#include "Service.h"
#include "Observer.h"
#include <string>

class QuestionAndAnswerSite : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    QuestionAndAnswerSite(Service& service, std::string name, QWidget *parent = Q_NULLPTR);

private:
    Ui::QuestionAndAnswerSiteClass ui;
    Service& service;
    std::string name;

    void populateList();
    void connectSignalsAndSlots();
    void update() override;

    void addQuestion();
    void addAnswer();
    void populateAnswersList();
    void spinBox();
    void changeVotes();

    int getSelectedIndex() const;
    int getSelectedIndexAnswers() const;
};
