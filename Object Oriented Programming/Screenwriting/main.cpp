#include "Screenwriting.h"
#include <QtWidgets/QApplication>
#include <string>
#include "Service.h"
#include "TapesTableModel.h"
#include <QSortFilterProxyModel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	std::ifstream fileIn("writers.txt");
	Writer currentWriter;
	std::string path{ "ideas.txt" };
	std::shared_ptr<Repository<Idea>> ideas = std::make_shared<FileRepository<Idea>>(path);
	Service service{ *ideas.get()};
	//QSortFilterProxyModel* filterModel = new QSortFilterProxyModel{};
	TapesTableModel* model = new TapesTableModel{ *ideas.get() };
	/*filterModel->setSourceModel(model);
	filterModel->sort(3, Qt::AscendingOrder);*/
	while (fileIn >> currentWriter)
	{
		Screenwriting* windows = new Screenwriting(service, model, currentWriter);
		windows->setWindowTitle(QString::fromStdString(currentWriter.getName()));
		service.addObserver(windows);
		windows->show();
	}
	fileIn.close();
    return a.exec();
}
