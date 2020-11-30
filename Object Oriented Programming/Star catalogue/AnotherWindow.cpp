#include "AnotherWindow.h"
#include <QPainter>

AnotherWindow::AnotherWindow(Service& service, std::string constellation, QWidget *parent)
	:service(service), constellation(constellation), QWidget(parent)
{
	ui.setupUi(this);
	this->paint();
}

AnotherWindow::~AnotherWindow()
{
}

QSize AnotherWindow::sizeHint() const
{
	return QSize{ 600, 400 };
}

void AnotherWindow::paint()
{
	QPainter painter{ this };
	painter.eraseRect(0, 0, 600, 400);
	std::vector<Star> allStars = this->service.getAll();
	for (auto star : allStars)
	{
		if (star.getConstellation() == constellation)
		{
			QPen pen2{ Qt::black, 1, Qt::SolidLine, Qt::RoundCap };
			painter.setPen(pen2);
			painter.drawEllipse(star.getRA(), star.getDec(), star.getDiameter(), star.getDiameter());
		}
	}
}

void AnotherWindow::update()
{
	this->paint();
}

void AnotherWindow::paintEvent(QPaintEvent* event)
{
	this->paint();
}
