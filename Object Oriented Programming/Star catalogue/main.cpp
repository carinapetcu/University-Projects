#include "Exam.h"
#include "Service.h"
#include "Domain.h"
#include "ChartWidget.h"
#include <QtWidgets/QApplication>
#include "Tests.h"
#include "TableModel.h"

int main(int argc, char *argv[])
{
	testAll();
    QApplication a(argc, argv);
	std::ifstream fileIn("astronomers.txt");
	Astronomer astronomer;
	std::string pathStars{ "stars.txt" };

	std::shared_ptr<Repository<Star>> stars = std::make_shared<FileRepository<Star>>(pathStars);
	Service service{ *stars.get() };
	TableModel* model = new TableModel{ *stars.get() };
	while (fileIn >> astronomer)
	{
		Exam* window = new Exam(service, astronomer, model);
		window->setWindowTitle(QString::fromStdString(astronomer.getName()));
		service.addObserver(window);
		window->show();
	}
	fileIn.close();
    return a.exec();
}
