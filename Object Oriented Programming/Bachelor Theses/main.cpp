#include "bachelorTheses.h"
#include "ChartWidget.h"
#include <QtWidgets/QApplication>
#include "Service.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	std::ifstream fileIn("teachers.txt");
	std::string teacherName;
	std::string pathStudents{ "students.txt" };
	std::shared_ptr<Repository<Student>> student = std::make_shared<FileRepository<Student>>(pathStudents);
	Service service{ *student.get()};
	while (fileIn >> teacherName)
	{
		bachelorTheses* window = new bachelorTheses(service, teacherName);
		window->setWindowTitle(QString::fromStdString(teacherName));
		service.addObserver(window);
		window->show();
	}
	fileIn.close();
	ChartWidget* chart = new ChartWidget{ service };
	service.addObserver(chart);
	chart->show();
    return a.exec();
}
