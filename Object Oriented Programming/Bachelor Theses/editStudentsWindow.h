#pragma once

#include <QWidget>
#include "ui_editStudentsWindow.h"
#include "Service.h"
#include "Observer.h"

class editStudentsWindow : public QWidget, public Observer
{
	Q_OBJECT

public:
	editStudentsWindow(Service& service, std::string name, QWidget *parent = Q_NULLPTR);
	~editStudentsWindow();

private:
	Ui::editStudentsWindow ui;
	Service& service;
	std::string name;
	void populateList();
	void connectSignalsAndSlots();
	void update();
	void editStudent();

	int getSelectedIndex() const;
};
