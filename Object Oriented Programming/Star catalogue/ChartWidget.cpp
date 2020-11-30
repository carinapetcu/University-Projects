#include "ChartWidget.h"
#include <qlayout.h>
#include <qtcharts/qbarset>
#include <qtcharts/qbarseries>
#include <QtCharts/qabstractaxis.h>
#include <QtCharts/qbarcategoryaxis.h>
#include <QtCharts/qchart.h>
#include <QtCharts/qvalueaxis.h>
#include <QtCharts/qchartview.h>


using namespace QtCharts;

ChartWidget::ChartWidget(Service& newService) : service{ newService }
{
	this->initializeChartWidget();
}

void ChartWidget::update()
{
	this->initializeChartWidget();
}

void ChartWidget::initializeChartWidget()
{
	std::vector<Student> allStudents = this->service.getAll();
	std::vector<std::string> allSections{};
	std::vector<std::string> uniqueSections{};
	for (auto student : allStudents)
	{
		allSections.push_back(student.getCoordinator());
		if (std::find(uniqueSections.begin(), uniqueSections.end(), student.getCoordinator()) == uniqueSections.end())
		{
			uniqueSections.push_back(student.getCoordinator());
		}
	}

	QBarSeries* series = new QBarSeries();

	std::sort(uniqueSections.begin(), uniqueSections.end());

	for (auto section : uniqueSections)
	{
		QBarSet* set = new QBarSet(QString::fromStdString(section));
		int numberOfOccurrences = std::count(allSections.begin(), allSections.end(), section);
		*set << numberOfOccurrences;
		series->append(set);
	}

	QChart* chart = new QChart();
	chart->addSeries(series);
	chart->setTitle("Number of students/ teacher");

	QBarCategoryAxis* axisX = new QBarCategoryAxis();
	chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(axisX);

	QValueAxis* axisY = new QValueAxis();
	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);
	axisY->setRange(0, 5);

	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);

	QChartView* chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	auto mainLayout = new QVBoxLayout{ this };
	mainLayout->addWidget(new QChartView(chart));
	this->setLayout(mainLayout);

}


