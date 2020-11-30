#pragma once

#include <QWidget>
#include "ui_myListTable.h"
#include "TapesTableModel.h"

class myListTable : public QWidget
{
	Q_OBJECT

public:
	myListTable(TapesTableModel* model, QWidget *parent = Q_NULLPTR);
	void update();
	~myListTable();

private:
	Ui::myListTable ui;
	TapesTableModel* model;
};
