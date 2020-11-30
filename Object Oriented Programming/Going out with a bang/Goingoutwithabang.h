#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Goingoutwithabang.h"
#include "TapesTableModel.h"
#include "Service.h"
#include "myListTable.h"

class Goingoutwithabang : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    Goingoutwithabang(Service& service, QWidget *parent = Q_NULLPTR);

private:
    Ui::GoingoutwithabangClass ui;
    Service& service;
	QShortcut* shortcutUndoModeA;
	QShortcut* shortcutUndoModeB;
	QShortcut* shortcutRedoModeA;
	QShortcut* shortcutRedoModeB;
	myListTable* table;

	int position;
    void update() override;
	void populateList();
	void connectSignalsAndSlots();
	void createShortcuts();

	int getSelectedIndexModeA() const;
	int getSelectedIndexModeB() const;
	void addTape();
	void deleteTape();
	void updateTape();

	void addOnWatchList();
	void nextWatchList();
	void showList();
	void filterList();
	void openTable();

	void undoModeA();
	void redoModeA();
	void undoModeB();
	void redoModeB();
};
