#pragma once

#include <QWidget>
#include "ui_AnotherWindow.h"
#include "Service.h"
#include <QtWidgets/QMainWindow>
#include <QPen>

class AnotherWindow : public QWidget, public Observer
{
	Q_OBJECT

public:
	AnotherWindow(Service& service, std::string constellation, QWidget *parent = Q_NULLPTR);
	QSize sizeHint() const Q_DECL_OVERRIDE;
	~AnotherWindow();

private:
	Ui::AnotherWindow ui;
	Service& service;
	std::string constellation;
	void paint();
	void update();

protected:
	void paintEvent(QPaintEvent* event) override;

};
