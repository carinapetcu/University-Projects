#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Quiz.h"
#include "Service.h"

class Quiz : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    Quiz(Service& service, Participant participant, QWidget *parent = Q_NULLPTR);

private:
    Ui::QuizClass ui;
    Service& service;
    Participant participant;

    void populateList();
    void connectSignalsAndSlots();
    void update() override;

    void answerQuestion();
    void setAnswerButton();
    int getSelectedIndex() const;
};
