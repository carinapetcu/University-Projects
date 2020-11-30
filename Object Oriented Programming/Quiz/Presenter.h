#pragma once

#include <QWidget>
#include "ui_Presenter.h"
#include "Service.h"
#include "Observer.h"

class Presenter : public QWidget, public Observer
{
	Q_OBJECT

public:
	Presenter(Service& service, QWidget *parent = Q_NULLPTR);
	~Presenter();

private:
	Ui::Presenter ui;
	Service& service;

	void populateList();
	void connectSignalsAndSlots();
	void update() override;

	void addQuestion();
};
