#include "myListTable.h"
#include "PictureDelegate.h"

myListTable::myListTable(TapesTableModel* model, QWidget *parent)
	: model{model}, QWidget(parent)
{
	ui.setupUi(this);
	
	ui.myListTableView->setModel(this->model);
	ui.myListTableView->setItemDelegate(new PictureDelegate{});

	// force the columns to resize, according to the size of their contents
	ui.myListTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.myListTableView->resizeColumnsToContents();
	ui.myListTableView->resizeRowsToContents();
	
}

void myListTable::update()
{
	this->model->update();
}

myListTable::~myListTable()
{
}
