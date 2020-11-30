#pragma once
#include <qwidget.h>
#include "Service.h"
#include "Observer.h"

class ChartWidget : public QWidget, public Observer
{
private:
	Service& service;
public:
	ChartWidget(Service& newService);
	void update();
	void initializeChartWidget();
};

