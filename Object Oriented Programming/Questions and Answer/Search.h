#pragma once

#include <QWidget>
#include "ui_Search.h"
#include "Service.h"
#include "Observer.h"

class Search : public QWidget, public Observer
{
	Q_OBJECT

public:
	Search(Service& service, QWidget *parent = Q_NULLPTR);
	~Search();

private:
	Ui::Search ui;
	Service& service;

	void connectSignalsAndSlots();
	void filterList();
	void update() override;
};
